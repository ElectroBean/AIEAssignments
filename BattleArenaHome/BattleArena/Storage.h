#pragma once
template<class T>
class Storage
{
public:
	Storage<T>(const int a_iCapacity)
	{
		m_iCapacity = a_iCapacity;
		m_data = new T[m_iCapacity]{ 0 };
		m_iSize = 0;
	}
	~Storage()
	{
		delete[] m_data;
		m_data = nullptr;
	}

	void add(const T& a_iteam)
	{
		if (m_iSize == m_iCapacity)
		{
			Storage::Expand();
		}
		m_data[m_iSize] = a_iteam;
		++m_iSize;
	}

	T& operator[](const int& a_iIndex)
	{
		return m_data[a_iIndex];
	}

private:
	void Expand()
	{
		m_iCapacity *= 2; //doubles the capacity
		T* newStorage = new T[m_iCapacity]{ 0 }; //
		for (int i = 0; i < m_iSize; ++i)
		{
			newStorage[i] = m_data[i];
		}
		delete[] m_data;
		m_data = newStorage;
		newStorage = nullptr;
	}
	T* m_data;		 //array data
	int m_iCapacity; //array capacity
	int m_iSize;	 //array size
};

