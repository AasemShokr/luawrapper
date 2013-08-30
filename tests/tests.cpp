#include <iostream>
#include <LuaContext.hpp>

void test1() {
	LuaContext context;

	auto val = context.executeCode<int>("return 3");
	if (val != 3)			throw std::logic_error("Test 1 failed");

	auto val2 = context.executeCode<std::string>("return 'hello'");
	if (val2 != "hello")	throw std::logic_error("Test 1 failed");
}

void test2() {
	LuaContext context;
	context.executeCode("a = 2");
	if (!context.hasVariable("a"))
		throw std::logic_error("Test 2 failed");
	if (context.readVariable<int>("a") != 2)
		throw std::logic_error("Test 2 failed");
}

void test3() {
	LuaContext context;

	context.writeVariable("a", true);

	if (!context.hasVariable("a"))
		throw std::logic_error("Test 3 failed");
	if (context.readVariable<bool>("a") != true)
		throw std::logic_error("Test 3 failed");
}

void test4() {
	LuaContext context;

	context.writeVariable<std::function<int (int)>>("foo", [](int i) { return i + 2; });

	const auto val = context.executeCode<int>("return foo(3)");
	if (val != 5)	throw std::logic_error("Test 4 failed");
}

int main() {
	test1();
	test2();
	test3();
	test4();

	std::cout << "All tests are successful" << std::endl;
	return 0;
}
