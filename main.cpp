#include <cassert>
#include <utility>

class my_class
{
public:
  my_class(const int x = 0) noexcept : m_x(x) {}
  my_class(my_class&& other) noexcept : m_x(other.m_x)
  {
    const_cast<int&>(other.m_x) = 0;
  }
  my_class(const my_class&) = delete;
  my_class& operator=(const my_class&) = delete;

  int GetX() const noexcept { return m_x; }

private:
  ///'const int' is trivial, imaging this being a 'const Database' instead
  const int m_x;
};

int main()
{
  my_class a(42);
  assert(a.GetX() == 42);

  //Initialize b with the internals of a,
  //leave a without its internals
  const my_class b { std::move(a) };

  assert(a.GetX() == 0);
  assert(b.GetX() == 42);
}