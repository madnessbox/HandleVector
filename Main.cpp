#include <iostream>;
#include "HandleArray.hpp";

int main()
{
	entity_handle_array_t handle_array;
	entity_handle_array_init(&handle_array, 10);

	entity_t entity1;
	entity_components_t entity_components1;
	entity_components1.components = 5;
	
	entity_t entity2;
	entity_components_t entity_components2;
	entity_components2.components = 12;

	entity_t entity3;
	entity_components_t entity_components3;
	entity_components3.components = 23;

	entity1 = *entity_handle_array_add(&handle_array, &entity_components1);
	entity2 = *entity_handle_array_add(&handle_array, &entity_components2);
	entity3 = *entity_handle_array_add(&handle_array, &entity_components3);


	std::cout << "entity1 id: " << entity1.id << std::endl;
	std::cout << "entity2 id: " << entity2.id << std::endl;
	std::cout << "entity3 id: " << entity3.id << std::endl;

	std::cout << "entity1 data: " << entity_handle_array_get_data(&handle_array, &entity1)->components << std::endl;
	std::cout << "entity2 data: " << entity_handle_array_get_data(&handle_array, &entity2)->components << std::endl;
	std::cout << "entity3 data: " << entity_handle_array_get_data(&handle_array, &entity3)->components << std::endl;
	
	// --------------------------


	std::cout << std::endl;

	entity_handle_array_remove(&handle_array, entity2);

	std::cout << "entity1 id: " << entity1.id << std::endl;
	std::cout << "entity3 id: " << entity3.id << std::endl;

	std::cout << "entity1 data: " << entity_handle_array_get_data(&handle_array, &entity1)->components << std::endl;
	std::cout << "entity3 data: " << entity_handle_array_get_data(&handle_array, &entity3)->components << std::endl;
	
	// --------------------------


	std::cout << std::endl;

	entity_t entity4;
	entity_components_t entity_components4;
	entity_components4.components = 47;
	entity4 = *entity_handle_array_add(&handle_array, &entity_components4);

	std::cout << "entity1 id: " << entity1.id << std::endl;
	std::cout << "entity3 id: " << entity3.id << std::endl;
	std::cout << "entity4 id: " << entity4.id << std::endl;

	std::cout << "entity1 data: " << entity_handle_array_get_data(&handle_array, &entity1)->components << std::endl;
	std::cout << "entity3 data: " << entity_handle_array_get_data(&handle_array, &entity3)->components << std::endl;
	std::cout << "entity4 data: " << entity_handle_array_get_data(&handle_array, &entity4)->components << std::endl;

	// --------------------------


	std::cout << std::endl;

	entity_t entity5;
	entity_components_t entity_components5;
	entity_components5.components = 64;
	entity5 = *entity_handle_array_add(&handle_array, &entity_components5);

	std::cout << "entity1 id: " << entity1.id << std::endl;
	std::cout << "entity3 id: " << entity3.id << std::endl;
	std::cout << "entity4 id: " << entity4.id << std::endl;
	std::cout << "entity5 id: " << entity5.id << std::endl;

	std::cout << "entity1 data: " << entity_handle_array_get_data(&handle_array, &entity1)->components << std::endl;
	std::cout << "entity3 data: " << entity_handle_array_get_data(&handle_array, &entity3)->components << std::endl;
	std::cout << "entity4 data: " << entity_handle_array_get_data(&handle_array, &entity4)->components << std::endl;
	std::cout << "entity5 data: " << entity_handle_array_get_data(&handle_array, &entity5)->components << std::endl;

	// --------------------------


	std::cout << std::endl;

	entity_handle_array_remove(&handle_array, entity1);
	entity_handle_array_remove(&handle_array, entity5);

	data_array_component_t* entities_data = nullptr;
	unsigned int num_entities = entity_handle_array_get_array(&handle_array, &entities_data);


	return 1;
}