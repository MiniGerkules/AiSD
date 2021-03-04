#include "CppUnitTest.h"
#include "../associative_array/map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		Map<int, int>* map;

		TEST_METHOD_INITIALIZE(init)
		{
			map = new Map<int, int>();
		}

		TEST_METHOD_CLEANUP(clean)
		{
			delete map;
		}

		TEST_METHOD(get_root_test)
		{
			map->insert(1, 25);

			Assert::AreEqual(1, map->get_root()->get_key());
			Assert::AreEqual(25, map->get_root()->get_value());
		}

		TEST_METHOD(test_insert_left_turn)
		{
			Iterator<int, int>* bft;
			int abs_res[] = { 2, 1, 3 };
			size_t i;

			map->insert(1, 25);
			map->insert(2, 15);
			map->insert(3, 5);

			bft = map->create_bft_iterator();
			for (i = 0; i < 3; ++i)
				Assert::AreEqual(abs_res[i], bft->next()->get_key());

			delete bft;
		}

		TEST_METHOD(test_insert_right_turn)
		{
			Iterator<int, int>* bft;
			int abs_res[] = { 3, 1, 5 };
			size_t i;

			map->insert(5, 25);
			map->insert(3, 15);
			map->insert(1, 5);

			bft = map->create_bft_iterator();
			for (i = 0; i < 3; ++i)
				Assert::AreEqual(abs_res[i], bft->next()->get_key());

			delete bft;
		}

		TEST_METHOD(test_insert_repainting)
		{
			Iterator<int, int>* bft;
			int abs_res[] = { 2, 1, 3, 4 };
			size_t i;

			map->insert(1, 25);
			map->insert(2, 15);
			map->insert(3, 5);
			map->insert(4, 0);

			bft = map->create_bft_iterator();
			for (i = 0; i < 4; ++i)
				Assert::AreEqual(abs_res[i], bft->next()->get_key());

			delete bft;
		}

		TEST_METHOD(test_insert_complex)
		{
			Iterator<int, int>* bft;
			int abs_res[] = { 13, 8, 17, 1, 11, 15, 25, 6, 22, 27 };
			size_t i;

			map->insert(13, 5);
			map->insert(8, 9);
			map->insert(17, 20);
			map->insert(25, 2);
			map->insert(15, -20);
			map->insert(1, -3);
			map->insert(11, -8);
			map->insert(27, 1000);
			map->insert(6, -576);
			map->insert(22, 13);

			bft = map->create_bft_iterator();
			for (i = 0; i < 10; ++i)
				Assert::AreEqual(abs_res[i], bft->next()->get_key());

			delete bft;
		}

		TEST_METHOD(create_bft_iterator_test)
		{
			Iterator<int, int>* bft;

			try
			{
				bft = map->create_bft_iterator();
			}
			catch (std::out_of_range(exeption))
			{
				Assert::AreEqual("There are no elements in the RB-tree!", exeption.what());
			}
		}

		TEST_METHOD(bft_iterator_test)
		{
			map->insert(5, 25);
			map->insert(3, 15);
			map->insert(1, 5);
			map->insert(4, -13);
			map->insert(-1, 5);
			map->insert(2, 89);

			Iterator<int, int>* bft = map->create_bft_iterator();
			Assert::AreEqual(map->get_root()->get_key(), bft->next()->get_key());
			Assert::AreEqual(1, bft->next()->get_key());
			Assert::AreEqual(5, bft->next()->get_key());
			Assert::AreEqual(-1, bft->next()->get_key());
			Assert::AreEqual(2, bft->next()->get_key());
			Assert::AreEqual(4, bft->next()->get_key());
		}

		TEST_METHOD(find_in_empty_test)
		{
			try
			{
				map->find(5);
			}
			catch (domain_error error)
			{
				Assert::AreEqual("The item with the passed key does not exist!", error.what());
			}
		}

		TEST_METHOD(find_test)
		{
			map->insert(13, 5);
			map->insert(8, 9);
			map->insert(17, 20);
			map->insert(25, 2);
			map->insert(15, -20);
			map->insert(1, -3);
			map->insert(11, -8);
			map->insert(27, 1000);
			map->insert(6, -576);
			map->insert(22, 13);

			Assert::AreEqual(map->find(22)->get_value(), 13);
			Assert::AreEqual(map->find(1)->get_value(), -3);
			Assert::AreEqual(map->find(13)->get_value(), 5);
		}

		TEST_METHOD(get_keys_test)
		{
			vector<int> abs_res = { 13, 8, 17, 1, 11, 15, 25, 6, 22, 27 };

			map->insert(13, 5);
			map->insert(8, 9);
			map->insert(17, 20);
			map->insert(25, 2);
			map->insert(15, -20);
			map->insert(1, -3);
			map->insert(11, -8);
			map->insert(27, 1000);
			map->insert(6, -576);
			map->insert(22, 13);

			vector<int>* res = map->get_keys();
			for (size_t i = 0; i < abs_res.size(); i++)
				Assert::AreEqual(abs_res[i], (*res)[i]);
		}

		TEST_METHOD(get_values_test)
		{
			vector<int> abs_res = { 5, 9, 20, -3, -8, -20, 2, -576, 13, 1000 };

			map->insert(13, 5);
			map->insert(8, 9);
			map->insert(17, 20);
			map->insert(25, 2);
			map->insert(15, -20);
			map->insert(1, -3);
			map->insert(11, -8);
			map->insert(27, 1000);
			map->insert(6, -576);
			map->insert(22, 13);

			vector<int>* res = map->get_values();
			for (size_t i = 0; i < abs_res.size(); i++)
				Assert::AreEqual(abs_res[i], (*res)[i]);
		}


		TEST_METHOD(clear_test)
		{
			map->insert(13, 5);
			map->insert(8, 9);
			map->insert(17, 20);
			map->insert(25, 2);
			map->insert(15, -20);
			map->insert(1, -3);
			map->insert(11, -8);
			map->insert(27, 1000);
			map->insert(6, -576);
			map->insert(22, 13);

			map->clear();

			try
			{
				Iterator<int, int>* bft = map->create_bft_iterator();
			}
			catch (std::out_of_range exeption)
			{
				Assert::AreEqual("There are no elements in the RB-tree!", exeption.what());
			}
		}

		TEST_METHOD(easy_remove_test)
		{
			int abs_res[] = { 13, 8, 17, 1, 11, 15, 25 };

			map->insert(13, 5);
			map->insert(8, 9);
			map->insert(17, 20);
			map->insert(25, 2);
			map->insert(15, -20);
			map->insert(1, -3);
			map->insert(11, -8);
			map->insert(27, 1000);
			map->insert(6, -576);
			map->insert(22, 13);

			// Remove the leaf
			map->remove(6);
			map->remove(22);
			map->remove(27);

			Iterator<int, int>* bft = map->create_bft_iterator();
			for (size_t i = 0; i < 7; ++i)
			{
				Assert::AreEqual(abs_res[i], bft->next()->get_key());
			}
		}

		TEST_METHOD(average_remove_test)
		{
			int abs_res[] = { 13, 8, 17, 6, 11, 15, 25, 22, 27 };

			map->insert(13, 5);
			map->insert(8, 9);
			map->insert(17, 20);
			map->insert(25, 2);
			map->insert(15, -20);
			map->insert(1, -3);
			map->insert(11, -8);
			map->insert(27, 1000);
			map->insert(6, -576);
			map->insert(22, 13);

			// Removing an element with 1 descendant
			map->remove(1);

			Iterator<int, int>* bft = map->create_bft_iterator();
			for (size_t i = 0; i < 9; ++i)
			{
				Assert::AreEqual(abs_res[i], bft->next()->get_key());
			}
		}

		TEST_METHOD(hard_remove_test)
		{
			vector<int> abs_res = { 15, 8, 25, 1, 11, 17, 27, 6, 22 };

			map->insert(13, 5);
			map->insert(8, 9);
			map->insert(17, 20);
			map->insert(25, 2);
			map->insert(15, -20);
			map->insert(1, -3);
			map->insert(11, -8);
			map->insert(27, 1000);
			map->insert(6, -576);
			map->insert(22, 13);

			// Removing an element with two children
			map->remove(13);

			Iterator<int, int>* bft = map->create_bft_iterator();
			for (size_t i = 0; i < 9; ++i)
			{
				Assert::AreEqual(abs_res[i], bft->next()->get_key());
			}
		}
	};
}
