using namespace std;

namespace ValpoRobotics {
/**
 * \class array
 *
 * \ingroup Containers
 * <!-- (Note, this needs exactly one \defgroup somewhere) -->
 *
 * \brief container that allows each member to be accessed in a range based for loop
 *
 * This container exists because std::array is unavaliable under arduino for no apparent reason.
 * Do not use this in a non arduino context, use boost::array or std::array
 *
 * \note Do not use this in a non arduino context.
 *
 * \author  <!-- ((last to touch it) --> Bill Sullivan
 *
 * \version $Revision: 1.0 
 *
 * \date  2018/08/14 14:16:20
	<!-- YYYY/MM/DD -->
 * 
 *
 * Created on: 2018/04/14 14:16:20
 */

	template <typename T, int SIZE>
	class array{
	public:
		/**
		* \brief underlying array
		*/
		T arr[SIZE];
		/**
		* \brief pointer to the start of the array
		*/
		T* pBegin = &(arr[0]);
		/**
		* \brief pointer to the nex unused avaliable position in the array
		*/
		T* pEnd = pBegin;		
		/**
		* \brief function that returns pBegin implemented so range based for loop will work
		*/
		T* begin() {
			return pBegin;
		}
		/**
		* \brief function that returns pEnd implemented so range based for loop will work
		*/
		T* end() {
			return pEnd;
		}		
		
		/**
		* \brief places an element in the next avaliable position if avaliable 
		*/
		void push_back(T nextElement) {			
			if (SIZE >= pEnd - pBegin) {
				*(pEnd) = nextElement;
				pEnd = pEnd + 1;				
			}
		}
	};
}