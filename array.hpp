using namespace std;

namespace ValpoRobotics {

	template <typename T, int SIZE>

	class array{
	public:
		T arr[SIZE];
		
		T* pBegin = &(arr[0]);
		T* pEnd = pBegin;		

		T* begin() {
			return pBegin;
		}

		T* end() {
			return pEnd;
		}		

		void push_back(T nextElement) {
			//*(pEnd - 1) = nextElement;	
			if (SIZE >= pEnd - pBegin) {
				*(pEnd) = nextElement;
				pEnd = pEnd + 1;				
			}
		}
	};
}