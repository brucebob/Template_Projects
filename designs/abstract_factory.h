#pragma once

namespace factory
{
	template <typename T>
	class BaceProcess
	{
	public:
		virtual void process(T& t)=0;
		virtual ~BaceProcess()
		{

		}
	};
	
	
	template<typename T>
	class BaceProcessFactory
	{
	private:
		std::list<BaceProcess<T>*> process_list;
	public:
		virtual void config()=0;
		BaceProcessFactory<T>()
		{

		}
		void process(T& t)
		{
			for(std::list<BaceProcess<T>*>::iterator itor = process_list.begin(); itor != process_list.end(); itor++)
			{
				(*itor)->process(t);
			}
		}
		BaceProcessFactory<T>& operator=(const BaceProcessFactory<T>& t)
		{
			if(this != &t)
			{
				process_list = t.process_list;
			}
			return *this;
		}
		BaceProcessFactory<T>(const BaceProcessFactory<T>& t)
		{
			process_list = t.process_list;
		}
	protected:
		void add_process(BaceProcess<T>* t)
		{
			process_list.push_back(t);
		}
		~BaceProcessFactory()
		{
			while(!process_list.empty())
			{
				delete process_list.front();
				process_list.pop_front();
			}
		}
	};
};