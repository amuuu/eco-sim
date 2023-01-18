#include "pch.h"

#include "GameSystems/GeneralTools/DoubleSidedMap.h"
using namespace General;

#include <string>

static DoubleSidedMap<int, std::string> Populate()
{
	DoubleSidedMap<int, std::string> m;

	m.Add(1, "Hello");
	m.Add(2, "Wassup");
	m.Add(3, "Lesgoo");
	
	return m;
}

TEST(DoubleSidedMap, Create) 
{
	DoubleSidedMap<int, std::string> m = Populate();

	EXPECT_EQ(m.Get("Wassup"), 2);
	EXPECT_EQ(m.Get(3), "Lesgoo");
}

TEST(DoubleSidedMap, Remove)
{
	DoubleSidedMap<int, std::string> m = Populate();

	m.Remove(2);
	m.Remove("Hello");

	EXPECT_EQ(m.GetSize(), 1);
}