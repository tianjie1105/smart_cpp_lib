#include "unit_test/tut/tut/tut.hpp"

#include <type_traits>
#include "multi_thread/tls.hpp"


namespace tut
{
	struct tls
	{};

	typedef test_group<tls> tf;
	typedef tf::object object;
	tf tls_group("tls");

	template<>
	template<>
	void object::test<1>()
	{
		set_test_name("tls_ptr");

		multi_thread::tls_ptr_t<int> tls_val;

		int val = 10;
		tls_val = &val;
		
		ensure("tls_ptr", 10 == *tls_val);

		struct test_type
		{} t;

		multi_thread::call_stack_t<test_type>::context ctx(&t);
		ensure("tls_ptr", multi_thread::call_stack_t<test_type>::contains(&t));
	}


	template<>
	template<>
	void object::test<2>()
	{
		set_test_name("tls");

		typedef std::remove_reference<decltype(*this)>::type T;
		multi_thread::call_stack_t<T>::context ctx(this);
		ensure("tls contain", multi_thread::call_stack_t<T>::contains(this));
	}

}