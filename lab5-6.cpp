#include <iostream>

using namespace std;

class Drug
{
    private:
        char* name;
        double cost;
        bool isPrescription;
        char* country;
        int form;

    public:
        Drug() : name(nullptr), cost(0.0), isPrescription(false), country(nullptr), form(int(1)) {}
        
        Drug(const char* name, double cost, bool isPrescription, const char* country, int form)
        {
            this->name = new char[strlen(name) + 1];
            strcpy_s(this->name, strlen(name) + 1, name);

            this->cost = cost;
            this->isPrescription = isPrescription;

            this->country = new char[strlen(country) + 1];
            strcpy_s(this->country, strlen(country) + 1, country);

            this->form = form;
        }

        Drug(const Drug& other)
        {
            name = new char[strlen(other.name) + 1];
            strcpy_s(name, strlen(other.name) + 1, other.name);

            cost = other.cost;
            isPrescription = other.isPrescription;

            country = new char[strlen(other.country) + 1];
            strcpy_s(country, strlen(other.country) + 1, other.country);

            form = other.form;
        }

        ~Drug()
        {
            delete[] name;
            delete[] country;
        }

        void print() const
        {
            std::cout << "Drug name: " << name << ", Cost: " << cost 
            << ", Prescription: " << (isPrescription ? "Yes" : "No" ) << ", Country: " << country 
            << ", Form: " << form << "\n";
        }

        void setName(const char* newName) 
        {
            delete[] name;
            name = new char[strlen(newName) + 1];
            strcpy_s(name, strlen(newName) + 1, newName);
        }

        void setCost(double cost)
        {
            this->cost = cost;
        }

        void setIsPrescription(bool isPrescription)
        {
            this->isPrescription = isPrescription;
        }

        void setCountry(const char* newCountry) 
        {
            delete[] country;
            country = new char[strlen(newCountry) + 1];
            strcpy_s(country, strlen(newCountry) + 1, newCountry);
        }


        void setForm(int form)
        {
            this->form = form;
        }

        static Drug findMostExpensiveDrug(Drug* drugs, int size, const char* country)
        {
            double maxCost = 0.0;
            int maxCostIndex = -1;

            for (int i = 0; i < size; ++i)
            {
                if (strcmp(drugs[i].country, country) == 0 && drugs[i].cost > maxCost)
                {
                    maxCost = drugs[i].cost;
                    maxCostIndex = i;
                }
            }

            if (maxCostIndex == -1)
            {
                std::cout << "No drug found!" << std::endl;
                return Drug();
            }

            return drugs[maxCostIndex];
        }

        static double prescriptionRatio(Drug* drugs, int size, const char* country)
        {
            int prescriptionCount = 0;
            int totalCount = 0;

            for (int i = 0; i < size; ++i)
            {
                if (strcmp(drugs[i].country, country) == 0)
                {
                    ++totalCount;
                    if (drugs[i].isPrescription)
                    {
                        ++prescriptionCount;
                    }
                }
            }

            return totalCount > 0 ? (double)prescriptionCount / totalCount : 0.0;
        }

        static void listDrugsByForm(Drug* drugs, int size, int form)
        {
            std::cout << "Drugs with form " << form << ":\n";
            for (int i = 0; i < size; ++i)
            {
                if (drugs[i].form == form)
                {
                    drugs[i].print();
                }
            }
        }
};

int main()
{
    Drug d1("Paracetamol", 200.0, false, "USA", 1);
    d1.print();

    d1.setCost(250.0);
    d1.print();

    Drug drugs[] = 
    {
        Drug("Paracetamol", 200.0, false, "USA", 1),
        Drug("Aspirin", 150.0, false, "UK", 2),
        Drug("Ibuprofen", 300.0, false, "USA", 3),
    };

    int size = sizeof(drugs) / sizeof(Drug);

    Drug mostExpensiveDrug = Drug::findMostExpensiveDrug(drugs, size, "USA");
    std::cout << "Most expensive drug in USA: ";
    mostExpensiveDrug.print();

    double prescriptionRatio = Drug::prescriptionRatio(drugs, size, "USA");
    std::cout << "Prescription ratio in USA: " << prescriptionRatio << std::endl;

    Drug::listDrugsByForm(drugs, size, 1);

    return 0;
}
