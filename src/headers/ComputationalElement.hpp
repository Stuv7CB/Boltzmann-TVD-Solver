#pragma once
#include "Point.hpp"
#include "Element.hpp"

class ComputationalElement
{
private:
    Element element;
    double value;
public:
    ComputationalElement(Element &element) : element(element)
    {
    }

    ComputationalElement(Element &&element) : element(std::move(element))
    {
    }

    ComputationalElement(ComputationalElement &el) : element(el.element)
    {

    }

    ComputationalElement(ComputationalElement &&el) : element(std::move(el.element))
    {

    }

    double getValue() const
    {
        return value;
    }

    void setValue(const double &value)
    {
        this->value = value;
    }

    void countNewValue(Point p)
    {
        //value = (value - gamma
        //for each direction of speed
        //count value as speed_x value
    }
};
