#pragma once

#include <memory>
#include <array>
#include <iostream>
#include <vector>

class ISolution
{
public:
    virtual std::vector<double> get() = 0;
    virtual void show() = 0;
    virtual ~ISolution(){}
};

class Infinite : public ISolution
{
public:
    std::vector<double> get() override {return {};}
    void show() override{std::cout << "Inf" << std::endl;}
};

class OneRoot : public ISolution
{
public:
    std::vector<double> get() override {std::vector<double> r; r.push_back(m_root); return r;}
    OneRoot(const double i_root) : m_root(i_root){}
    void show() override{ std::cout << m_root << std::endl;}
private:
    const double m_root;
};

class TwoRoots : public ISolution
{
public:
    std::vector<double> get() override {std::vector<double> r; r.push_back(m_x1); r.push_back(m_x2); return r;}
    TwoRoots(const double i_x1, const double i_x2) : m_x1(i_x1), m_x2(i_x2){}
    void show() override{std::cout << m_x1 << ' ' << m_x2 << std::endl;}
private:
    const double m_x1;
    const double m_x2;
};

class NoSolution : public ISolution
{
public:
    std::vector<double> get() override {return {};}
    void show() override{std::cout << "No solution" << std::endl;}
};

namespace Solver{

std::unique_ptr<ISolution> solve(const std::array<double, 3>& i_input);

}
