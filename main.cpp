
#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <chrono>
#include <algorithm>

bool is_divisible(const unsigned long& d, const unsigned long& n)
{
return d % n == 0;
}

bool is_prime(const unsigned long& d)
{
unsigned long d_sqrt = (unsigned long)std::sqrt(d);
for (unsigned long n = 2; n <= d_sqrt; ++n)
   {
   if (is_divisible(d, n))
      return false;
   }

return true;
}

void recursive_find
   (
   const unsigned long& num,
   const std::vector<unsigned long>& tens,
   const size_t& tens_index,
   const unsigned long& max_num,
   std::vector<unsigned long>& output
   )
{
if (tens_index >= tens.size())
   return;

const unsigned long& t = tens[tens_index];
for (unsigned long d = 1; d <= 9; ++d)
   {
   unsigned long n = (d * t) + num;
   if (n < max_num && is_prime(n))
      {
      output.push_back(n);
      recursive_find(n, tens, tens_index + 1, max_num, output);
      }
   }
}

int main(int argc, const char * argv[])
{
auto start = std::chrono::steady_clock::now();

std::vector<unsigned long> tens;
unsigned long e31 = std::pow(2, 31);
for (unsigned long i = 10; i < e31; i *= 10)
   tens.push_back(i);

std::vector<unsigned long> output = { 2, 3, 5, 7 };
recursive_find(3, tens, 0, e31, output);
recursive_find(7, tens, 0, e31, output);
std::sort(output.begin(), output.end());

auto time = (std::chrono::steady_clock::now() - start).count() / 1000000;

std::cout << "Found [" << output.size() << " numbers] in [" << time << " ms]" << std::endl;
std::vector<size_t> test_inputs = { 20, 197, 200 };
for (auto i : test_inputs)
   std::cout << " Number " << i << ": " << output[i - 1] << std::endl;

return 0;
}
