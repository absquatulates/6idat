#include <iostream>
#include <vector>

class Bacteria_colony
{
public:
    Bacteria_colony(int bacteria, double consumption)
        : bacteria{bacteria}, consumption{consumption}
    {}
    virtual ~Bacteria_colony() = default;
    
    virtual double update(double  nutrients)
    {
        return nutrients;
    }

    virtual void print()
    {
        std::cout << bacteria << std::endl;
    }

protected:
    int bacteria{};
    double consumption{};
    
};

class Ecoli : public Bacteria_colony
{
public:
    Ecoli(int bacteria, double consumption, double growthFactor, double growthRate)
        : Bacteria_colony(bacteria, consumption), growthFactor{growthFactor}, growthRate{growthRate} 
    {}
    double update(double nutrients) override
    {

        if(nutrients > bacteria * consumption)
        {
            bacteria = bacteria * growthFactor;
            growthFactor = growthFactor * growthRate;
            nutrients -= (bacteria * consumption);
        }
        return nutrients;
    }

    void print() override
    {
        std::cout << "E-coli count: " << bacteria << " with growth factor: " << growthFactor << std::endl; 
    }
    

private:
    double growthFactor{};
    double growthRate{};
};

class Saureus : public Bacteria_colony
{
public:
    using Bacteria_colony::Bacteria_colony;
    
    void print() override
    {
        std::cout << "S-aureus count: " << bacteria << std::endl; 
    }
    double update(double nutrients) override
    {

        if(nutrients > bacteria * consumption)
        {
            bacteria = bacteria * 3;
            nutrients = nutrients - (bacteria * consumption);
            nutrients -= (bacteria * consumption);
        }
        return nutrients;
    }
    
};


class Petri_Dish
{
public:
    Petri_Dish(std::vector<Bacteria_colony> colonies, double nutrients)
        : colonies{colonies}, nutrients{nutrients}
    {}
    void simulate(Ecoli & ecoli, Saureus & saureus)
    {

        ecoli.update(nutrients);
        saureus.update(nutrients);

    }

    void print(Ecoli & ecoli, Saureus & saureus)
    {
        ecoli.print();
        saureus.print();
        std::cout << "Nutrients: " << nutrients << std::endl;
    }
private:

   
    std::vector<Bacteria_colony> colonies{};
    double nutrients{};


};
    

int main()
{
    Ecoli ecoli{1, 1.0, 2.0, 1.5};
    Saureus saureus{1, 2.0};
    
    std::vector<Bacteria_colony> colonies { ecoli, saureus };

    
    Petri_Dish dish{colonies, 600};

    dish.print(ecoli, saureus);

    std::cout << "Simulating 5 time steps..." << std::endl;
    for(int i{}; i < 5; ++i)
    {
        dish.simulate(ecoli, saureus);
    }

    dish.print(ecoli, saureus);
}
