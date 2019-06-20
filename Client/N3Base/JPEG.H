#ifndef _JPEG_MODULE_BODY_
#define _JPEG_MODULE_BODY_

#include "shared/types.h"

struct SET
{
	uint8_t C[3]; // Y, Cb, Cr ����
};

struct DQT
{
	uint8_t Q[64]; // Qantization Table ��
};

struct DHT
{
	BOOL Flag; 
	int Num;
	uint16_t *HUFFCODE; // ������ �ڵ�
	uint8_t *HUFFSIZE; // ������ �ڵ��� ����
	uint8_t *HUFFVAL;  // ������ �ڵ尡 ��Ÿ���� ��
	uint16_t MAXCODE[17]; // �ش� ���̿��� ���� ū �ڵ�
	uint16_t MINCODE[17]; // �ش� ���̿��� ���� ���� �ڵ�
	int VALPTR[17]; // �ش� ������ �ڵ尡 ���۵Ǵ� �ε���
	int *PT; // VALUE�� INDEX�� ������ ã�� ���� ������
};

struct FRAMEHEADER
{
	uint16_t Y; // �̹����� ����
	uint16_t X; // �̹����� ����
	uint8_t Nf; // ������Ʈ ��
	uint8_t C[3]; // ������Ʈ ���̵�
	uint8_t H[3]; // ������Ʈ�� Horizontal Sampling Factor
	uint8_t V[3]; // ������Ʈ�� Vertical Sampling Factor
	uint8_t Tq[3]; // �ش� ������Ʈ�� ���Ǵ� ����ȭ���̺� ��ȣ
};

struct SCANHEADER
{
	uint8_t Ns; // ������Ʈ ��
	uint8_t Cs[3]; // ������Ʈ ���̵�
	uint8_t Td[3]; // ������Ʈ�� DC Huffman Table ��ȣ
	uint8_t Ta[3]; // ������Ʈ�� AC Huffman Table ��ȣ
	uint8_t Ss;
	uint8_t Se;
	uint8_t Ah;
	uint8_t Al;
};


class CJpeg  
{
public:

	// JPEG File�� Load�ϱ� ���� �Լ��� //
	void LoadJPG(LPCSTR FileName); // JPEG File�� Load�ϴ� �Լ�	
	void FindSOI(); // Start of Image ��Ŀ�� ã�� �Լ�
	void FindDQT(); // Quantization Table�� ã�� ����ü�� �����ϴ� �Լ�
	void FindDHT();	// Huffman Table�� ã�� ����ü�� �����ϴ� �Լ�
	void FindSOF(); // Frame Header�� ã�� ����ü�� �����ϴ� �Լ�
	void FindSOS(); // Scan Header�� ã�� ����ü�� �����ϴ� �Լ�
	void FindETC(); // DRI(Define Restart Interval) �ε� 
	void Decode();  // ���ڵ带 ���� ������ �����ϰ� ���ڵ带 ����
	void DecodeMCU(int mx, int my); // MCU������ ���ڵ��ϴ� �Լ�
	void DecodeDU(int N); // 8x8 Data Unit�� ���ڵ��ϴ� �Լ�
	void IDCT(); // Inverse DCT�� �ϴ� �Լ�
	void Zigzag(); // Zigzag������ �Ǿ��ִ� DU�� ���󺹱ͽ�Ű�� �Լ�
	void DecodeAC(int Th); // DU��, AC������ ���ڵ��ϴ� �Լ�
	void DecodeDC(int Th); // DU��, DC������ ���ڵ��ϴ� �Լ�
	int16_t Extend(uint16_t V, uint8_t T); // V�� ī�װ��� T�� �µ��� Ȯ��
	uint16_t Receive(uint8_t SSSS); // ���ۿ��� SSSS��Ʈ��ŭ �о���� �Լ�
	uint8_t hDecode(int Th); // ������ ��ȣ�� ���ڵ��ϴ� �κ�
	uint8_t NextByte(); // ���ۿ��� ���� 1 ����Ʈ�� �о���� �Լ�
	uint16_t NextBit(); // ���ۿ��� ���� 1 ��Ʈ�� �о���� �Լ�
	void ConvertYUV2RGB(); // ���ڵ�� �����͸� �÷����� �ٲް� ���ÿ�
						   // ��Ʈ�ʿ� ȣȯ�ǵ��� ��ȯ�ϴ� �Լ�
	
	
	// JPEG File�� Save�ϱ� ���� �Լ��� //	
	void SaveJPG(LPCSTR FileName, int Width, int Height, uint8_t *pp); // JPEG ������ �����ϴ� �Լ�

	void PutSOI(HANDLE hFile); // Start of Image ��Ŀ�� ����
	void PutDQT(HANDLE hFile); // Quantizatino Table�� ����
	void PutDHT(HANDLE hFile); // Huffmann Table�� ����
	void PutSOF(HANDLE hFile, int Width, int Height); // FrameHeader�� ����
	void PutSOS(HANDLE hFile); // ScanHeader�� ����
	void PutEOI(HANDLE hFile); // End of Image ��Ŀ�� ����

	void ShotBit(uint8_t Bit); // 1��Ʈ�� ���ۿ� �����ϴ� �Լ�
	void ChargeCode(uint16_t Code, int Size ); // Size��ŭ�� ����(�Ʒ��ڸ��κ���)�� Code�� ���ۿ� �����ϴ� �Լ�
	void EncodeDU(int16_t *pos, BOOL Flag, int bWidth); // 8x8 Block�� ���ڵ��ϴ� �Լ�
	void hEncode(int bWidth, int bHeight); // ������ ���ڵ� �ϴ� �κ�
	uint8_t GetCategory(int16_t V); // �־��� ���� ī�װ����� ���ϴ� �Լ�	
	void Zigzag2(); // Zigzag������ ����� �Լ�
	void DCT(int16_t *pos, int bWidth, BOOL Flag); // DCT�� �� �� Zigzag �� Quantization �ϴ� �Լ�

	int GetHeight(); // �̹����� ���̸� ��ȯ�ϴ� �Լ�
	int GetWidth();	// �̹����� ���̸� ��ȯ�ϴ� �Լ�
	
	uint16_t Ri; // Restart Interval
	int m_rWidth; // �̹����� �������� ����
	int m_rHeight; // �̹����� �������� ����
	uint8_t * pByte; // NextByte()�Լ����� ����
	
	int cnt; // ��Ʈ������ ������ �� ���̴� ī����
	
	int16_t *Y;  // Save�� �� ���̴� Y Buffer
	int16_t *Cb; // Save�� �� ���̴� Cb Buffer
	int16_t *Cr; // Save�� �� ���̴� Cr Buffer

	SET *MCU; // MCU ������ ����
	
	uint8_t Hmax; // Maximum Horizontal Sampling Factor
	uint8_t Vmax; // Maximum Vertical Sampling Factor
	
	uint8_t * m_pData;	// �̹��� ����
	uint8_t * m_pBuf; // ����
	int m_Index; // ������ ��ġ�� ��Ÿ���� �ε���
	DQT TbQ[20]; // Quantization Table
	DHT TbH[20]; // Huffman Table
	int16_t ZZ[64]; // 8x8 Block ������ ��� �迭
	FRAMEHEADER FrameHeader; // FrameHeader ����ä
	SCANHEADER ScanHeader; // ScanHeader ����ü
	int16_t PrevDC[3]; // DC ������ Predictor

	
	CJpeg();
	virtual ~CJpeg();

};

#endif //_JPEG_MODULE_BODY_