#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#define TRUE  (1 == 1)
#define FALSE (1 == 0)

// table de partition
typedef struct {
    u_int8_t etatPartition;     // 1
    u_int8_t teteLectureDebut;  // 2
    u_int16_t secteurDebut:6;   // suite
    u_int16_t cylindreDebut:10; // 3, 4
    u_int8_t type;              // 5
    u_int8_t teteLectureFin;    // 6
    u_int16_t secteurFin:6;     // 7, 8
    u_int16_t cylindreFin:10;   // suite
    u_int32_t distance;         // 9, 10, 11, 12
    u_int32_t nombreSecteur;    // 13, 14, 15, 16
} __attribute__ ((packed)) TablePartition;

// Maxi Boot Root
typedef struct {
    u_int8_t code[0x1BE];       // code d'amorçage
    TablePartition entreeTablePartition[4]; // table de partitions
    u_int8_t codeSecteurPartition[2];   // code secteur
} __attribute__ ((packed)) MBR;

// listes des types de partition
char   *typePartition[] = {
    "00", "01 FAT12", "02 XENIX root", "03 XENIX usr",
    "04 FAT16 <32M", "05 Extended", "06 FAT16", "07 HPFS/NTFS",
    "08 AIX", "09 AIX bootable", "0A OS/2 Boot Manager", "0B Win95 FAT32",
    "0C Win95 FAT32 (LBA)", "0D", "0E Win95 FAT16 (LBA)",
        "0F Win95 Ext'd (LBA)",
    "10 OPUS", "11 Hidden FAT12", "12 Compaq diagnostics",
    "14 Hidden FAT16 <32M", "15", "16 Hidden FAT16", "17 Hidden HPFS/NTFS",
    "18 AST SmartSleep", "19", "1A", "1B Hidden Win95 FAT32",
    "1C Hidden Win95 FAT32", "1D", "1E Hidden Win95 FAT16", "1F",
    "20", "21", "22", "23",
    "24 NEC DOS", "25", "26", "27",
    "28", "29", "2A", "2B",
    "2C", "2D", "2E", "2F",
    "30", "31", "32", "33",
    "34", "35", "36", "37",
    "38", "39 Plan 9", "3A", "3B",
    "3C PartitionMagic recov   (FAT-12/16/32)", "3D", "3E", "3F",
    "40 Venix 80286", "41 PPC PReP Boot", "42 SFS", "43",
    "4C", "4D QNX4.x", "4E QNX4.x 2nd part", "4F QNX4.x 3rd part"
        "50 OnTrack DM", "51 OnTrack DM6 Aux1", "52 CP/M",
        "53 OnTrack DM6 Aux3",
    "54 OnTrackDM6", "55 EZ-Drive", "56 Golden Bow", "57",
    "58", "59", "5A", "5B",
    "5C Priam Edisk", "5D", "5E", "5F",
    "60", "61 SpeedStor", "62", "63 GNU HURD or SysV",
    "64 Novell Netware 286", "65 Novell Netware 386", "66", "67",
    "68", "69", "6A", "6B",
    "6C", "6D", "6E", "6F",
    "70 DiskSecure Multi-Boot", "71", "72", "73",
    "74", "75 PC/IX", "76", "77",
    "78", "79", "7A", "7B",
    "7C", "7D", "7E", "7F",
    "80 Old Minix", "81 Minix / old Linux", "82 Linux swap", "83 Linux",
    "84 OS/2 hidden C: drive", "85 Linux extended", "86 NTFS volume set",
        "87 NTFS volume set",
    "88", "89", "8A", "8B",
    "8C", "8D", "8E Linux LVM", "8F",
    "90", "91", "92", "93 Amoeba",
    "94 Amoeba BBT", "95", "96", "97",
    "98", "99", "9A", "9B",
    "9C", "9D", "9E", "9F BSD/OS",
    "A0 IBM Thinkpad hiberna", "A1", "A2", "A3",
    "A4", "A5 FreeBSD", "A6 OpenBSD", "A7 NeXTSTEP",
    "A8 Darwin UFS", "A9 NetBSD", "AA", "AB Darwin boot",
    "AC", "AD", "AE", "AF",
    "B0", "B1", "B2", "B3",
    "B4", "B5", "B6", "B7 BSDI fs",
    "B8 BSDI swap", "B9", "BA", "BB Boot Wizard hidden",
    "BC", "BD", "BE Solaris boot", "BF",
    "C0", "C1 DRDOS/sec (FAT-12)", "C2", "C3",
    "C4 DRDOS/sec (FAT-16 < 32Mb)", "C5", "C6 DRDOS/sec (FAT-16)", "C7 Syrinx",
    "C8", "C9", "CA", "CB",
    "CC", "CD", "CE", "CF",
    "D0", "D1", "D2", "D3",
    "D4", "D5", "D6", "D7",
    "D8", "D9", "DA Non-FS data", "DB CP/M / CTOS / ...",
    "DC", "DD", "DE Dell Utility", "DF BootIt",
    "E0", "E1 DOS access", "E2", "E3 DOS R/O",
    "E4 SpeedStor", "E5", "E6", "E7",
    "E8", "E9", "EA", "EB BeOS fs",
    "EC", "ED", "EE EFI GPT", "EF EFI",
    "F0 Linux/PA-RISC boot", "F1 SpeedStor", "F2 DOS secondary", "F3",
    "F4 SpeedStor", "F5", "F6", "F7",
    "F8", "F9", "FA", "FB",
    "FC", "FD Linux raid autodetec", "FE LANstep", "FF BBT"
};

int main(int argc, char *argv[])
{
    int     f;                  // descripteur
    unsigned int i;             // compteur
    MBR     mbr;                // structure MBR

    if (argc != 2)
    {
        printf("Usage: %s <fichier image MBR>\n", argv[0]);
        exit(1);
    }

    // variable pour tester l'architecture
    int     j = 0x01020304;
    char   *p;

    // ouverture du fichier associé au 1er disque dur
    // nécessite le droit de lecture
    if ((f = open(argv[1], O_RDONLY)) == -1)
    {
        printf("Erreur d'ouverture du fichier %s: %s.\n",
               argv[1],
               strerror(errno));
        return -1;
    }

#ifdef DEBUG
    // vérification de la taille des variables
    printf("Taille d'un secteur: %d\n", sizeof(mbr));
    printf("Taille d'une entrée: %d\n", sizeof(TablePartition));
    printf("Taille du code: %d\n", sizeof(mbr.code));
    printf("Taille des entrée: %d\n", sizeof(mbr.entreeTablePartition));
    printf("Taille du code de partition: %d\n\n",
           sizeof(mbr.codeSecteurPartition));
    //printf("Taille du cylindre de début: %d\n\n", sizeof(mbr.entreeTablePartition[0].cylindreDebut));
#endif

    // remplir la structure mbr
    bzero(&mbr, 512);           // initialisé à zéro
    read(f, &mbr, 512);         // lire le fichier
    close(f);

    // lire les 4 entrée de la table de partition
    for (i = 0; i < 4; i++)
    {
        printf("Entrée Partition %u\n", i);
        if (mbr.entreeTablePartition[i].type)
        {
            printf("\tEtat: %0X\n", mbr.entreeTablePartition[i].etatPartition);
            printf("\tType: %s\n",
                   typePartition[mbr.entreeTablePartition[i].type]);
            printf("\tTête de lecture début: %u\n",
                   mbr.entreeTablePartition[i].teteLectureDebut);
            printf("\tCylindre de début: %u\n",
                   mbr.entreeTablePartition[i].cylindreDebut);
            printf("\tSecteur de début: %u\n",
                   mbr.entreeTablePartition[i].secteurDebut);
            printf("\tTête de lecture fin: %u\n",
                   mbr.entreeTablePartition[i].teteLectureFin);
            printf("\tCylindre de fin: %u\n",
                   mbr.entreeTablePartition[i].cylindreFin);
            printf("\tSecteur de fin: %u\n",
                   mbr.entreeTablePartition[i].secteurFin);
            printf("\tDistance: %u\n", mbr.entreeTablePartition[i].distance);
            printf("\tNombre de Secteur: %u\n",
                   mbr.entreeTablePartition[i].nombreSecteur);
        }
        else
        {
            printf("\tAucune entrée.\n");
        }
        printf("\n");
    }

    printf("Code d'identification: %X%X.\n\n",
           mbr.codeSecteurPartition[0], mbr.codeSecteurPartition[1]);

    // tester l'architecture
    printf("Architecture: ");
    p = (char *)&j;             /*   int * transformé en char *   */
    if (*p++ == 1 && *p++ == 2 && *p++ == 3 && *p++ == 4)
    {
        printf("big endian.\n");
    }
    else
    {
        p = (char *)&j;
        if (*p++ == 4 && *p++ == 3 && *p++ == 2 && *p++ == 1)
            printf("little endian.\n");
        else
            printf("exotique !!\n");
    }

    return 0;
}
