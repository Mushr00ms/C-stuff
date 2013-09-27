#include <stdio.h>//printf()
#include <string.h>//strlen()

typedef unsigned int int_32;
typedef unsigned short int int_16;
typedef unsigned char int_8;

typedef union 
{
	int_32 Valeur;
	struct 
	{
		int_8 Entree;
		int_16 Reste __attribute__((packed));
		int_8 Sortie;
	}Partie;

}CRC16_Partie;


static CRC16_Partie _CRC16;

const int polynome_crc = 0x1021; // polynome 16 bits CITT
const int crc_initiale = 0xFFFF; // valeur initial du CRC

void octetCRC16(int_8 octet)
{
	int nombreOctet = 8;
	_CRC16.Partie.Entree = octet;
	do
	{
		_CRC16.Valeur <<= 1;
		if(_CRC16.Partie.Sortie & 0x01)
			_CRC16.Partie.Reste ^= polynome_crc;
	}while(--nombreOctet);
}

int_16 StringToCRC16(char * s)
{
	_CRC16.Partie.Reste = crc_initiale;
	int i = 0;
	int size = strlen(s);
	for(i = 1; i <= size; i++)
		octetCRC16(s[i]);
	octetCRC16(0x00);
	octetCRC16(0x00);

	return _CRC16.Partie.Reste;
}
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage : %s <string>\n",argv[0]);
		return -1;
	}
	char * chaine = argv[1];
	printf("CRC `%s` : 0x%x \n",chaine,StringToCRC16(chaine));

	return 0;
}