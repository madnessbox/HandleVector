#pragma once

typedef struct entity {
	unsigned int generation;
	unsigned int id;
} entity_t;

// Array B
typedef struct entity_components {
	unsigned int components;
} entity_components_t;

typedef struct handle {
	unsigned int generation;
	unsigned int index;
} handle_t;

typedef struct health_component {
	unsigned int health;
} health_component_t;

typedef struct data_array_component {
	entity_t entity;
	entity_components_t entity_components;
} data_array_component_t;

typedef struct removed_entity_data {
	unsigned int data_array_index = -1;
	unsigned int handle_array_index = -1;
} removed_entity_data_t;

typedef struct entity_handle_array
{
	handle* handles = nullptr;

	data_array_component_t* data_array = nullptr;
	data_array_component_t* last_free = nullptr;
	data_array_component_t* last_used = nullptr;

	removed_entity_data_t* removed_entities_positions = nullptr;
	unsigned int NUM_REMOVED_ENTITIES = 0;

	unsigned int NUM_ENTITIES = 0;
	unsigned int MAX_NUM_ENTITIES;

} entity_handle_array_t;

void entity_handle_array_init(entity_handle_array_t* entity_handle_array, const unsigned int MAX_NUM_ENTITIES)
{
	entity_handle_array->MAX_NUM_ENTITIES = MAX_NUM_ENTITIES;

	entity_handle_array->handles = (handle_t*)malloc(MAX_NUM_ENTITIES * sizeof(handle_t));
	entity_handle_array->data_array = (data_array_component_t*)malloc(MAX_NUM_ENTITIES * sizeof(data_array_component_t));

	entity_handle_array->removed_entities_positions = (removed_entity_data_t*)malloc(MAX_NUM_ENTITIES * sizeof(removed_entity_data_t));

	entity_handle_array->last_free = entity_handle_array->data_array;
	entity_handle_array->last_used = entity_handle_array->data_array;
}

void entity_handle_array_destroy(entity_handle_array_t* entity_handle_array)
{
	free(entity_handle_array);
}

entity_t* entity_handle_array_add(entity_handle_array* entity_handle_array, entity_components_t* entity_components)
{
	if (entity_handle_array->NUM_ENTITIES >= entity_handle_array->MAX_NUM_ENTITIES)
	{
		return nullptr;
	}

	if (entity_handle_array->NUM_REMOVED_ENTITIES > 0)
	{
		removed_entity_data_t* removed_entity_data = &entity_handle_array->removed_entities_positions[entity_handle_array->NUM_REMOVED_ENTITIES - 1];

		entity_handle_array->data_array[removed_entity_data->data_array_index].entity_components = *entity_components;
		entity_handle_array->data_array[removed_entity_data->data_array_index].entity.id = removed_entity_data->handle_array_index;
		entity_handle_array->handles[removed_entity_data->handle_array_index].index = removed_entity_data->data_array_index;

		entity_handle_array->NUM_REMOVED_ENTITIES--;

		entity_handle_array->NUM_ENTITIES++;
		return &entity_handle_array->data_array[removed_entity_data->data_array_index].entity;
	}
	else
	{
		unsigned int new_entity_id = entity_handle_array->NUM_ENTITIES;
		entity_handle_array->last_free->entity_components = *entity_components;
		entity_handle_array->last_free->entity.id = new_entity_id;
		entity_handle_array->last_used = entity_handle_array->last_free;
		entity_handle_array->last_free++;

		unsigned int data_array_index = &(entity_handle_array->data_array[entity_handle_array->NUM_ENTITIES]) - entity_handle_array->data_array;
		entity_handle_array->handles[entity_handle_array->NUM_ENTITIES].index = data_array_index;

		entity_handle_array->NUM_ENTITIES++;
		return &entity_handle_array->last_used->entity;
	}
}

void entity_handle_array_remove(entity_handle_array_t* entity_handle_array, entity_t &entity)
{
	unsigned int entity_to_remove_data_array_index = entity_handle_array->handles[entity.id].index;
	unsigned int entity_to_remove_handle_array_index = entity.id;

	removed_entity_data_t removed_entity_data;
	removed_entity_data.data_array_index = entity_to_remove_data_array_index;
	removed_entity_data.handle_array_index = entity_to_remove_handle_array_index;

	entity_handle_array->removed_entities_positions[entity_handle_array->NUM_REMOVED_ENTITIES] = removed_entity_data;
	entity_handle_array->NUM_REMOVED_ENTITIES++;
	entity_handle_array->NUM_ENTITIES--;

	entity.id = -1;
}

entity_components_t* entity_handle_array_get_data(entity_handle_array_t* entity_handle_array, entity_t* entity)
{
	return &entity_handle_array->data_array[entity_handle_array->handles[entity->id].index].entity_components;
}

unsigned int entity_handle_array_get_array(entity_handle_array_t* entity_handle_array, data_array_component_t** data_array_component_out_ptr)
{
	data_array_component_t* data_array_out = (data_array_component_t*)malloc(entity_handle_array->NUM_ENTITIES * sizeof(data_array_component_t));

	if (entity_handle_array->NUM_REMOVED_ENTITIES > 0)
	{
		unsigned int out_index = 0;
		for (int i = 0; i < entity_handle_array->NUM_ENTITIES + entity_handle_array->NUM_REMOVED_ENTITIES; i++)
		{
			bool index_is_removed = false;
			for (int j = 0; j < entity_handle_array->NUM_REMOVED_ENTITIES; j++)
			{
				if (entity_handle_array->removed_entities_positions[j].data_array_index == i)
				{
					index_is_removed = true;
					break;
				}
			}

			if (!index_is_removed)
			{
				data_array_out[out_index] = entity_handle_array->data_array[i];
				out_index++;
			}

			if (out_index >= entity_handle_array->NUM_ENTITIES)
			{
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < entity_handle_array->NUM_ENTITIES; i++)
		{
			data_array_out[i] = entity_handle_array->data_array[i];
		}
	}
	*data_array_component_out_ptr = data_array_out;

	return entity_handle_array->NUM_ENTITIES;
}