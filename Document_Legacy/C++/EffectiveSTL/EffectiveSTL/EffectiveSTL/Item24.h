#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <string>
#include <array>
#include <set>
#include <memory>

//map::operator[]³ª map::insert´Â È¿À² ¹®Á¦¿¡ ÁÖÀÇÇÏ¿© ¼±ÅÃÇÏÀÚ

namespace Item24 {
	using namespace std;
	/*
		c++ 11ÀÇ move semanticÀÌ µµÀÔµÇ±â ÀÌÀüÀÇ ³»¿ëÀÓÀ» °¨¾ÈÇÕ½Ã´Ù.
		C++ 11ÀÌÈÄ map¿¡ emplace/emplace_hint ±â´ÉÀÌ Ãß°¡µÇ¾ú½À´Ï´Ù. insert¿Í ´Ş¸® »ğÀÔ½Ã ÀÓ½Ã°´Ã¼¸¦ »ı¼ºÇÏÁö ¾Ê½À´Ï´Ù.
		c++ 17ÀÌÈÄ insert_or_assign ±â´ÉÀÌ Ãß°¡µÇ¾ú½À´Ï´Ù.

		Ã¥ÀÌ ¾²ÀÎ ÀÌÈÄ·Î mapÀÇ ±â´ÉÀÌ ÃÖÀûÈ­ µÈ °Í °°½À´Ï´Ù. ÀÌ¹ø Ç×¸ñÀÇ ³»¿ëÀÌ ÀüºÎ ¸Â´Ù°í º¸±â ¾î·Æ½À´Ï´Ù.
	*/

	class Widget {
	public:
		Widget()						{ std::cout << "default ctor" << std::endl; }
		Widget(double)					{ std::cout << "double ctor" << std::endl; }
		~Widget()						{ std::cout << "dtor" << std::endl; }

		Widget(const Widget& rhs)		{ std::cout << "copy ctor" << std::endl; }
		Widget(Widget&& rhs) noexcept	{ std::cout << "move ctor" << std::endl; }
		//Widget(const Widget& rhs) = delete;
		//Widget(Widget&& rhs) noexcept = delete;

		Widget& operator=(double) {
			std::cout << "double operator =" << std::endl;
			return *this;
		}
		Widget& operator=(Widget&& rhs) noexcept {
			std::cout << "move operator =" << std::endl;
			return *this;
		}
	};

	/*
		¸Ê¿¡ »õ·Î¿î ¿ä¼Ò¸¦ "Ãß°¡"ÇÒ °æ¿ì¿¡´Â operator[]º¸´Ù insert°¡ È¿À²ÀûÀ¸·Î ³´½À´Ï´Ù.
		(ÇöÀç´Â ÀüºÎ ±×·¸´Ù°í º¸±â ¾î·Æ½À´Ï´Ù.)
	*/
	inline void AddElement() {
		map<int, Widget> m;
		/*
			´ÙÀ½ÀÇ Ç¥Çö½Ä
			m[k] = v;

			Àº ¿ì¼± ÇØ´ç ¸Ê¿¡ Å° k°¡ µé¾î ÀÖ´ÂÁö Á¡°ËÇÕ´Ï´Ù. 
			±×·¸Áö ¾Ê´Ù¸é k¿Í v°¡ Æä¾î·Î ¹­¿©¼­ ¸Ê¿¡ »õ·Î 'Ãß°¡'µË´Ï´Ù. 
			k°¡ ¸Ê¿¡ µé¾î ÀÖ´Â °æ¿ì¿¡´Â k¿Í ¸ÅÇÎ(¿¬°ü)µÈ °ª(value)ÀÌ v·Î °»½ÅµË´Ï´Ù.

			¸¸¾à¿¡ ÄÁÅ×ÀÌ³Ê ¾È¿¡ ÇØ´ç Å°¿¡ ´ëÀÀÇÏ´Â pair°ªÀÌ ¾ø´Ù°í ÇØº¾½Ã´Ù.
			operator[]´Â ÇØ´ç map¿¡ ÁöÁ¤µÈ °ª Å¸ÀÔ(value_type)ÀÇ ±âº» »ı¼ºÀÚ¸¦ »ç¿ëÇÏ¿© pair °´Ã¼¸¦ »õ·Î ¸¸µé°í, ÀÌ °´Ã¼ÀÇ ÂüÁ¶ÀÚ¸¦ ¹İÈ¯ÇÕ´Ï´Ù. 
			°á°úÀûÀ¸·Î, ¹İÈ¯µÈ Widget °´Ã¼ÀÇ ÂüÁ¶ÀÚ¸¦ ÅëÇØ operator=¿¬»êÀÚ ÇÔ¼ö°¡ È£ÃâµÇ¾î Widget °´Ã¼¿¡ °ªÀÌ ´ëÀÔµË´Ï´Ù.

			¾Æ·¡ÀÇ °æ¿ì operator[]¸¦ È£­ŒÇÒ ¶§ »õ·Î¿î pair¸¦ ¸¸µå´Â ±âº» »ı¼ºÀÚ°¡ È£ÃâµÇ°í, ±× ÀÌÈÄ double °ª 1.50¿¡ ´ëÇÑ ´ëÀÔ¿¬»êÀÚ°¡ È£ÃâµË´Ï´Ù.
			±âº» »ı¼ºÀÚ -> double ´ëÀÔ ¿¬»êÀÚ
			(copy elisionÀÌ Àû¿ëµÇ¸é¼­ °ª Ãß°¡ µ¿ÀÛÀÌ ÈÎ¾À ÃÖÀûÈ­ µÈ °Í °°½À´Ï´Ù.)
		*/
		cout << "============ operator[] =================" << endl;
		m[1] = 1.50;

		/*
			Ã¥¿¡¼­´Â insert¸¦ È°¿ëÇÏ´Â °ÍÀÌ ÇÔ¼ö È£Ãâ ºñ¿ëÀ» Å©°Ô ÁÙÀÏ ¼ö ÀÖ´Ù°í ¼³¸íµÇ¾î ÀÖ°í operator[]°¡ ÀÓ½Ã°´Ã¼¸¦ »ı¼ºÇÏ´Â °ÍÀÌ ±× ÀÌÀ¯¶ó°í ¼³¸íÇÕ´Ï´Ù.
			
			ÇöÀç ½ÇÇàÇØº¸¸é operator[]´Â ÀÓ½Ã °´Ã¼¸¦ µû·Î »ı¼ºÇÏÁö ¾ÊÀ¸¸ç ¿ÀÈ÷·Á insertÈ£ÃâÀÌ ÀÓ½Ã°´Ã¼¸¦ »ı¼ºÇÕ´Ï´Ù.

			¾Æ·¡ÀÇ °æ¿ì ¸¸¾àÀÇ Widget¾È¿¡ ÀÌµ¿»ı¼ºÀÚ°¡ ±¸ÇöµÇ¾î ÀÖÀ¸¸é
			double »ı¼ºÀÚ(ÀÓ½Ã°´Ã¼) -> ÀÌµ¿ »ı¼ºÀÚ -> ¼Ò¸êÀÚ(ÀÓ½Ã°´Ã¼) ¼øÀ¸·Î È£ÃâµÇ¸ç

			ÀÌµ¿»ı¼ºÀÚ°¡ ±¸ÇöµÇ¾î ÀÖÁö ¾Ê´Ù¸é
			double »ı¼ºÀÚ(ÀÓ½Ã°´Ã¼) -> º¹»ç »ı¼ºÀÚ -> ¼Ò¸êÀÚ(ÀÓ½Ã°´Ã¼) ¼øÀ¸·Î È£ÃâµË´Ï´Ù.

			insert°¡ ´õ È¿À²ÀûÀÌ¶ó°í º¸±â ¾î·Æ½À´Ï´Ù. 
		*/
		cout << "============ Insert =================" << endl;
		m.insert({ 2, 3.0 });

		
		//C++ 11ÀÌÈÄ map¿¡ emplace / emplace_hint ±â´ÉÀÌ Ãß°¡µÇ¾ú½À´Ï´Ù.insert¿Í ´Ş¸® »ğÀÔ½Ã ÀÓ½Ã°´Ã¼¸¦ »ı¼ºÇÏÁö ¾Ê½À´Ï´Ù.
		//double »ı¼ºÀÚ¸¦ ´Ü ÇÑ¹ø È£ÃâÇÕ´Ï´Ù.
		cout << "============ emplace =================" << endl;
		m.emplace(make_pair( 3, 3.0 ));

		cout << "============ Function End =================" << endl;
	}

	/*
		¹İ¸é¿¡, ¸Ê¿¡ ÀúÀåµÈ ¿ä¼Ò¿¡ ´ëÇÑ "°»½Å"À» ÇÒ °æ¿ì¿¡´Â insertº¸´Ù operator[]°¡ È¿À²ÀûÀ¸·Î³ª ¹Ì(Ú¸)ÀûÀ¸·Î³ª ³´½À´Ï´Ù.
	*/
	inline void UpdateElement() {
		map<int, int> m;
		m[1] = 10;
		m[2] = 10;

		// operator[]¸¦ ÅëÇØ 1¿¡ ¸ÅÇÎµÈ °ªÀ» 11·Î °»½ÅÇÕ´Ï´Ù.
		m[1] = 11;
		
		//insert¸¦ ÅëÇØ 2¿¡ ¸ÅÇÎµÈ °ªÀ» 11·Î °»½ÅÇÕ´Ï´Ù. ÀÓ½Ã°´Ã¼¸¦ »ı¼ºÇÏ´Â ºñ¿ëÀ» ÁöºÒÇØ¾ß ÇÕ´Ï´Ù.
		auto iter = m.insert(map<int, int>::value_type(2, 9));	
		iter.first->second = 11;
	}

	template <typename MapType, typename _Key, typename _Value>  
	decltype(auto) efficientAddOrUpdate(MapType& m, const _Key& k, const _Value& v)
	{
		// kÀÇ À§Ä¡ È¤Àº »ğÀÔ À§Ä¡¸¦ Ã£½À´Ï´Ù. lower_bound ´Â Ç×¸ñ 45 Âü°í
		auto lb = m.lower_bound(k);          

		//°ªÀ» °»½ÅÇÕ´Ï´Ù. 
		//lower_bound´Â µÎ °¡Áö ¸ñÀûÀ» °¡Áö°í È£ÃâÇÑ ¾Ë°í¸®ÁòÀÌ±â ¶§¹®¿¡ ½ÇÁ¦·Î ¿øÇÏ´Â Å° °ªÀ» Ã£¾Ò´ÂÁö Ã¼Å©ÇÏ´Â °úÁ¤ÀÌ ÇÑ¹ø ´õ ÇÊ¿äÇÕ´Ï´Ù.(µ¿µî¼º °Ë»ç ¼öÇà)
		if (lb != m.end() &&                 
			!(m.key_comp()(k, lb->first))) { 
			lb->second = v;                  
			return lb;                       
		}                                    
		else {
			//lb°¡ °¡¸®Å°´Â À§Ä¡¿¡ pair(k, v)¸¦ »ğÀÔÇÕ´Ï´Ù. 
			//insert¿¡¼­ ¹Ì¸® À§Ä¡¸¦ ÁöÁ¤ÇØÁØ´Ù¸é ·Î±× ½Ã°£ÀÌ ¾Æ´Ñ »ó¼ö ½Ã°£¿¡ ¿ø¼Ò »ğÀÔÀÌ °¡´ÉÇÕ´Ï´Ù.
			
			//return m.insert(lb, {k, v});        

			//c++ 11ÀÌÈÄ emplace_hint°¡ Ãß°¡µÇ¾ú½À´Ï´Ù. Á»´õ È¿À²ÀûÀ¸·Î ¿ø¼Ò »ğÀÔÀÌ °¡´ÉÇÕ´Ï´Ù.
			return m.emplace_hint(lb, k, v);
		}                                       
	}

	inline void AddOrUpdate() {
		map<int, Widget> m;
		cout << "============ efficientAddOrUpdate =================" << endl;
		cout << "============ Add =================" << endl;

		efficientAddOrUpdate(m, 1, 0.5);

		cout << "============ Update =================" << endl;

		efficientAddOrUpdate(m, 1, 1.5);

		cout << "============ Function End =================" << endl;
	}

	inline void RunSample() {
		AddElement();
		UpdateElement();
		AddOrUpdate();
	}
}
