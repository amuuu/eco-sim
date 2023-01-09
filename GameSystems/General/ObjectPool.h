//
// TODO: USE THIS GUY ~~~~
//


template<typename ObjectType, typename Identifier>
class ObjectPool
{
public:

	Identifier Add(ObjectType* r)
	{
		objects[nextID] = r;

		return nextID++;
	}

	ObjectType* Get(const Identifier& id)
	{
		return objects[id];
	}

private:

	std::map<const Identifier, ObjectType*> objects{};

	Identifier nextID { 0 };
};