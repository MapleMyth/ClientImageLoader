#ifdef CIL_EXPORTS
#define CIL_API __declspec(dllexport)
#else
#define CIL_API __declspec(dllimport)
#endif

class CIL_API APIDummy {
public:
	APIDummy(void);
};