#pragma once

#include "common.h"
#include "content.h"

namespace na
{
	class Application;

	class ContentManager
	{
	private:
		Application* m_app;

		//TODO: Good string hashing for speeding up these lookups
		s2::dict<s2::string, Content*> m_content;

	public:
		ContentManager(Application* app);
		~ContentManager();

		template<typename T>
		T* Get(const s2::string &filename)
		{
			try {
				auto pair = m_content.get_pair(filename);
				//TODO: Can we be safe without rtti?
				return dynamic_cast<T*>(pair.value());
			} catch (s2::dictexception) {}

			T* ret = new T(m_app);
			ret->Filename = filename;
			ret->Load(filename);
			m_content.add(filename, ret);
			return ret;
		}
	};
}
