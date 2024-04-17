#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <functional>
#include <chrono>

//std::bind���� ���ٸ� ��ȣ�϶�

namespace Item34 {
	using namespace std;
	using namespace placeholders;
	using namespace chrono;
	using Time = steady_clock::time_point;
	using Duration = steady_clock::duration;

	enum class Sound { Beep, Siren, Whistle };
	

	namespace Case0 {
		/*
			std::bind�� ����ϴ� �ͺ��� ���ٰ� �� �б� ���� ǥ������ ����. �׸��� �� ȿ������ �� �ִ�.
		*/

		using namespace literals;            // C++14 ���̻���� ���� �� �����ϰ� ǥ��

		void setAlarm(Time t, Sound s, Duration d)	// �ð� t���� �Ҹ� s�� �Ⱓ d��ŭ ����Ѵ�.
		{
			//...	
		}
		inline void RunSample() {
			auto setSoundL =
				[](Sound sound)
			{
				setAlarm(steady_clock::now() + hours(1),
					sound,
					seconds(30));
			};

			auto setSoundL2 =
				[](Sound sound)
			{
				setAlarm(steady_clock::now() + 1h,        // C++14 ���� �ǹ̴� ���� ����
					sound,
					30s);
			};

			//bind�� Ȱ���ϴ� ���
			auto setSoundB =                                // B�� bind�� ����
				std::bind(setAlarm,
					steady_clock::now() + 1h,            // ���� : SetAlarm �� ȣ��Ǵ� ������ �ƴ�, binding ��ü�� ��������� ������ �ð��� ���
					_1,
					30s);

			//�������� ���ĺ���
			/*
				���� �������� ���ĺ���

				* �߰������� nested bind ǥ������ ���(bind �Ű������� bind ��ü�� �ѱ� ��) ���� �ٱ��� bind ��ü�� operator() �� ȣ��� ��.
				���� bind ��ü�� operator()�� ���� ȣ��ǰ� �� ��ȯ ���� �ٱ��� bind ��ü�� operator()�� �Ű������� ���޵˴ϴ�.

				-> bind ��ü�� �״�� �Ű������� ���޵Ǵ� ���� �ƴմϴ�.
			*/
			auto setSoundB2 =
				std::bind(setAlarm,
					std::bind(std::plus<>(),			//c++14 ������ ǥ�� ������ ���ø��� ���� ���ø� Ÿ�� �μ��� ������ �� �ִ�. c++11�� �׷��� ���ϹǷ� Ÿ���� �ۼ��ؾ��Ѵ�.
						std::bind(steady_clock::now),
						1h),
					_1,
					30s);
		}
	}

	namespace Case1 {
		//���࿡ �����ε����� �߰��ȴٸ�

		enum class Volume { Normal, Loud, LoudPlusPlus };
		 
		void setAlarm(Time t, Sound s, Duration d)	
		{
			//...	
		}
		void setAlarm(Time t, Sound s, Duration d, Volume v)  
		{ 	
			//...
		}

		inline void RunSample() {

			//���ٴ� �������� �ʴ´�.
			auto setSoundL =
				[](Sound s)
			{
				setAlarm(steady_clock::now() + 1h,  
					s,                              
					30s);                           
			};

			// �ݸ� std::bind ������ �����ϵ��� �ʴ´�.
			//auto setSoundB =                                // ����! � setAlarm���� �𸥴�.
			//	std::bind(setAlarm,                           
			//		std::bind(std::plus<>(),
			//			std::bind(steady_clock::now),
			//			1h),
			//		_1,
			//		30s);

			using SetAlarm3ParamType = void(*)(Time t, Sound s, Duration d, Volume v);

			auto setSoundB =                                            
				std::bind(static_cast<SetAlarm3ParamType>(setAlarm),    //�����ε� ������ ��������� ��������� �Ѵ�.
					std::bind(std::plus<>(),
						std::bind(steady_clock::now),
						1h),
					_1,
					30s);
		}

		/*
			�� ��� ���ٿ� std::bind�� ��������
			 
			������ ��� setAlarm�� ȣ���� �ζ���ȭ (inlining)�� �� �ִ� ������ �Լ� ȣ���̴�.
			�ݸ�, std::bind�� ��� setAlarm�� �Լ� �����͸� ���� ȣ���ϴµ�, �Լ� �����͸� ���� �Լ��� ȣ���� �ζ���ȭ�� �� ���ɼ��� �۴�.
			
			��, ����ӵ� ���鿡�� ���ٸ� ����ϴ� ���� �� ȿ�����̴�.
		*/
	}

	namespace Case2 {
		//�ڵ尡 ����������
		inline void RunSample() {

			int lowVal = 0;
			int highVal = 100;

			auto betweenL = [lowVal, highVal](const auto& val)  // C++14
			{ 
				return lowVal <= val && val <= highVal; 
			};

			//bind Ȱ���� ���, �� �бⰡ �����
			auto betweenB =                                    // C++14
				std::bind(std::logical_and<>(),
					std::bind(std::less_equal<>(), lowVal, _1),
					std::bind(std::less_equal<>(), _1, highVal));

		}
	}

	namespace Case3 {
		//

		class Widget {	};

		enum class CompLevel { Low, Normal, High };      

		void compress(const Widget& w, CompLevel lev) {}
			

		inline void RunSample() {

			Widget w;

			auto compressRateB = std::bind(compress, w, _1);
			/*
				w �� binding ��ü�� ���� ���� ������ ���޵ȴ�.

				������, ��������� �巯���� �ʱ� ������ std::bind�� �۵� ����� �˰� �־�� �̸� �� �� �ִٴ� ���̴�.

				�ݸ� ���� ���ٹ�Ŀ��� w�� ������ �������Ǵ��� �ƴϸ� ������ �������Ǵ��� �ҽ� �ڵ忡 ����� �巯����.
			*/

			auto compressRateL = [w](CompLevel lev) // w�� ������ ĸ�ĵǰ� lev�� ������ ���޵ȴ�.
			{ 
				return compress(w, lev); 
			};

			compressRateL(CompLevel::High);
			compressRateB(CompLevel::High);
		}
	}
}