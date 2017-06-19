#ifndef OI_H
#define OI_H

class OI {
public:
	OI();

	static OI* GetInstance();

private:
	static OI* m_instance;
};

#endif  // OI_H
