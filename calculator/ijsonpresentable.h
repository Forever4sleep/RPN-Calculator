#pragma once
#include <nlohmann/json.hpp>

template <class T> class IJSONPresentable
{
	virtual T from_json(std::string key, nlohmann::json data) = 0;
};