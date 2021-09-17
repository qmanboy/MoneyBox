#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <ctime>

class Field 
{
    private:
        uint16_t m_field[10][10];
        std::ofstream m_tofile;
        std::ifstream m_fromfile;
        uint16_t m_temp;
    public:
        
        Field() 
        {            
            if (!fillfile()) 
            {
                fillfield();
            }            
        }
        
        void print() const 
        {
            std::cout << "\n";
            for (size_t idx = 0; idx < 10; ++idx) 
            {
                for (size_t jdx = 0; jdx < 10; ++jdx)
                {
                    std::cout << std::setw(5) << m_field[idx][jdx];
                }
                std::cout << "\n";
            }
        }

        bool fillfile() 
        {
            m_tofile.open("moneybox.lib", std::ios_base::app);
            m_tofile.seekp(0, std::ios::end);
            size_t size = m_tofile.tellp();
            if (size != 0) 
            {
                m_tofile.close();
                return false;
            }
            else 
            {
                for (size_t idx = 0; idx < 100; ++idx) 
                {
                    m_tofile  <<  (m_field[idx / 10][idx % 10] = (idx * 10) + 10) << ' ';
                }
                m_tofile.close();
                return true;
            }            
        }

        void fillfield() 
        {
            m_fromfile.open("moneybox.lib");
            for (size_t idx = 0; idx < 100; ++idx) 
            {
                m_fromfile >> m_field[idx / 10][idx % 10];
            }
            m_fromfile.close();
        }
};

class Process 
{
    private:
        Field m_field;
        uint16_t m_sum{0};
        uint16_t m_tempsum{0};
        uint16_t m_temp{0};
        std::vector<uint16_t> m_numbers;        
        size_t m_counter{0};
    public:
        Process() 
        {
            m_field.print();            
        }

        bool search_in_vector(uint16_t &_num) 
        {
            for (auto n : m_numbers) 
            {
                if (n == _num) 
                {
                    return true;
                }
            }
            return false;
        }

        void start() 
        {
            srand(time(NULL)); 
            std::cout << "Input cash >";
            std::cin >> m_sum;
            while (m_tempsum != m_sum) 
            {   
                if (m_counter++ < 100) 
                {                            
                    m_temp = (((rand() % 1000)/10)*10);
                }
                else 
                {
                    m_temp = m_sum - m_tempsum;
                }

                m_tempsum +=m_temp;
                if (m_tempsum > m_sum || search_in_vector(m_temp) || m_temp == 0) 
                {                    
                    m_tempsum -=m_temp;
                    continue;
                }
                else 
                {
                    m_numbers.push_back(m_temp);
                    std::cout << m_temp << "\n";
                }
            }            
        }
};

int main() 
{
    Process process;
    process.start();
    return 0;
}