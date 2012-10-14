#pragma once

namespace factory
{
	template <typename T>
	class Bace_Process
	{
	public:
		virtual void process(T& t)=0;
		virtual ~Bace_Process()
		{

		}
	};

	template<typename T>
	class Bace_Process_Factory
	{
	private:
		std::list<Bace_Process<T>*> process_list;
	public:
		virtual void config()=0;
		void process(T& t)
		{
			for(std::list<Bace_Process<T>*>::iterator itor = process_list.begin(); itor != process_list.end(); itor++)
			{
				(*itor)->process(t);
			}
		}
	protected:
		void add_process(Bace_Process<T>* t)
		{
			process_list.push_back(t);
		}
		~Bace_Process_Factory()
		{
			while(!process_list.empty())
			{
				delete process_list.front();
				process_list.pop_front();
			}
		}
	};
};
