template <typename T> struct Foo{
  auto Bar()
  {
    /*static T counter = 0;
    ++counter;
    if (counter != 1){
      return Bar();
    }
    return counter;
    */
    if(0){
      return T();
    }
    return Bar();
  }
};

template<typename T>
auto foo(T e)
{
  if(0) return e;
  return foo(e);
}
int main()
{
  Foo<int>().Bar();
  foo(1);
}

