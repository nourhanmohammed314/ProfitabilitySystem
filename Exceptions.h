#pragma once
#include <bits/stdc++.h>
class InvalidCostException : public std::runtime_error
{
public:
    InvalidCostException(const std::string &message) : std::runtime_error(message)
    {
    }
};
class ProductNotFoundException : public std::runtime_error
{
public:
    ProductNotFoundException(const std::string &message) : std::runtime_error(message)
    {
    }
};
class InvalidQuantityException : public std::runtime_error
{
public:
    InvalidQuantityException(const std::string &message) : std::runtime_error(message) {}
};
class InsufficientDataException : public std::runtime_error
{
public:
    InsufficientDataException(const std::string &message) : std::runtime_error(message)
    {
    }
};