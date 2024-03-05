#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <unordered_map>
#include <algorithm> 

using namespace std;

class CarInSales
{
	float reg_number;
	float tradein_number;
	float pret_cumparare;
	float pret_vanzare;
	float profit;
public:
	CarInSales(float reg_number, float tradin_number, float pret_cumparare, float pret_vanzare, float profit)
	{
		this->reg_number = reg_number;
		this->tradein_number = tradein_number;
		this->pret_cumparare = pret_cumparare;
		this->pret_vanzare = pret_vanzare;
		this->profit = profit;
	}
    float getRegistrationNumber() const
    {
        return reg_number;
    }
    float getTradeInNumber() const
    {
        return tradein_number;
    }

    float getPurchasePrice() const
    {
        return pret_cumparare;
    }
    float getSellingPrice() const
    {
        return pret_vanzare;
    }
    float getProfit() const
    {
        return profit;
    }
    void setProfit(float newProfit)
    {
        profit = newProfit;
    }

	// aici as face afisarea  void afisare(){} dar am facut hard-cooded
};

unordered_map<float, float> calculateProfits(const list<CarInSales>& cars)
{
    unordered_map<float, float> profits;
    for (const auto& car : cars)
    {
        float tradeInProfit = 0.0;
        if (car.getTradeInNumber() != 0.0)
        {
        
            tradeInProfit = profits[car.getTradeInNumber()] + car.getPurchasePrice();
        }
        float currentProfit = max(car.getSellingPrice() + tradeInProfit - car.getPurchasePrice(), 0.0);
        profits[car.getRegistrationNumber()] = currentProfit;
    }

    return profits;
}

void updateProfits(list<CarInSales>& cars)
{ 
    auto profits = calculateProfits(cars);
    for (auto& car : cars)
    {
        car.setProfit(profits[car.getRegistrationNumber()]);
    }
}



// aici as fi facut introducerea in lista  //void adaugare() list<CarInSales>



CarInSales MostProfitableCar(const list<CarInSales>& cars)
{
    // am folosit max_element din libraria <algorithm> pentru a gasi masina cu cel mai mare profit
    auto mostProfitableCar = max_element(cars.begin(), cars.end(),
        [](const CarInSales& car1, const CarInSales& car2) 
        {
            return car1.getPurchasePrice() < car2.getPurchasePrice();
        });

    return *mostProfitableCar;
}

int main()

{
    list<CarInSales> carList = {
    {1, 0, 20000.0, 25000.0, 0.0},
    {2, 1, 15000.0, 18000.0, 0.0},
    {3, 0, 30000.0, 0.0, 0.0}

    // aici am introdus valori hard-cooded // 
    };

    updateProfits(carList);
    for (const auto& car : carList)
    {
        cout << "Car: " << car.getRegistrationNumber() << ", Profit: " << car.getProfit() << endl;
    }

    CarInSales mostProfitableCar = MostProfitableCar(carList);
    cout << "Most Profitable Car: " << mostProfitableCar.getRegistrationNumber() << ", Profit: " << mostProfitableCar.getProfit() << endl;

    return 0;

	return 0;
}
