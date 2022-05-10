#pragma once

#include <string>
#include <map>

namespace GE
{
	template<typename T>
	class Manager
	{
	protected:
		std::map<std::string, T*> mapList;
	public:
		Manager() {}
		~Manager();
		void Add(T* newEntity, const std::string& name);
		T* Get(const std::string& name);
	};

	template<typename T>
	inline Manager<T>::~Manager()
	{
		for (auto& entity : mapList)
		{
			delete entity.second;
		}
	}

	template<typename T>
	inline void Manager<T>::Add(T* newEntity, const std::string& name)
	{
		mapList.insert(std::make_pair(name, newEntity));
	}

	template<typename T>
	inline T* Manager<T>::Get(const std::string& name)
	{
		return mapList.at(name);
	}
}