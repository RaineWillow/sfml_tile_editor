#ifndef Functor_hpp
#define Functor_hpp

template <typename ClassType, typename Result, typename Context>
class Functor
{
	typedef Result (ClassType::*FunctionType)(Context*);
	ClassType* obj;
	FunctionType fn;
public:
	Functor(ClassType& object, FunctionType method): obj(&object), fn(method) {}

	Result invoke(Context * context)
	{
		return (*obj.*fn)(context);
	}
};

#endif
