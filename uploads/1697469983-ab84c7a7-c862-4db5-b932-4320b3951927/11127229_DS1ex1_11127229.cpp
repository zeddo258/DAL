
// 11127229 �����Q

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <iostream>
using namespace std ;  // �ŧi�@�ӼзǨt�Ϊ��R�W�Ŷ�


// �g�c���O, �s���ܼƩM���
class Maze {
public:
    int goal ;  // �n�h���ؼЭӼ�
    int width ;
    int length ;
    char ** chartPtr = NULL ;  // ��������, ���F�ؤG���}�C
    void Set_chart( char info[100] ) ;
    void Access_data( FILE * fptr ) ;
    int Choice_path( int x, int y ) ;
    int record_path[30] ;  // �����g�L����V ( 1=�k 2=�U 3=�� 4=�W )
    void Initialize_record_path( ) ;
    int record_path_i ;
    char ** copy_chartPtr = NULL ;  // �e���|�|�Ψ�
    int passed_goal ;  // �g�L���ؼЭӼ�
    void Walk( ) ;
    int Walk_break( int x, int y ) ;
    void Print_chart( char ** ptr ) ;
    void Draw_route( ) ;
};


// �B�z��󤺪����, �����X��, ������}�l�B�z�g�c
void Maze::Access_data( FILE * fptr ) {
    char str[100], info[100] ;
    int str_i = 0, info_i = 0, len = 0 ;
    while ( 1 ) {
        if ( str_i == 0 ) {
            if ( fgets( str, 100, fptr ) == NULL ) break ;  // Ū����󤤪��r��, �@���@��
            len = strlen( str ) ;
        }

        if ( str[str_i] != ' ' && str[str_i] != '\0' && str[str_i] != '\n' ) {  // �o�����n���F��
            info[info_i] = str[str_i] ;  // �N�Ҧ����r���Ӷ��ǩ�J�}�C��
            info_i++ ;
        }

        str_i++ ;

        if ( str_i == len ) {  // �@�浲��
            str_i = 0 ;
        }
    }

    Set_chart( info ) ;
    Walk( ) ;
}


// �N��z�n������Ʃ�J�ئn���G���}�C��
void Maze::Set_chart( char info[100] ) {  // �Ϋ��ЫؤG���}�C
    chartPtr = ( char ** ) malloc( sizeof( char* ) * length ) ;  // ( �૬ ) ���t���s( �p����Ъ��r�` ���W ���X�� )
    for ( int i = 0 ; i < length ; i++ ) {
        chartPtr[i] = ( char * ) malloc( sizeof( char ) * width ) ;
    }

    copy_chartPtr = ( char ** ) malloc( sizeof( char* ) * length ) ;  // �ƻs�@���g�c
    for ( int i = 0 ; i < length ; i++ ) {
        copy_chartPtr[i] = ( char * ) malloc( sizeof( char ) * width ) ;
    }

    int info_i = 0 ;
    for ( int i = 0 ; i < length ; i++ ) {  // ��J���
        for ( int j = 0 ; j < width ; j++ ) {
            chartPtr[i][j] = info[info_i] ;
            copy_chartPtr[i][j] = info[info_i] ;
            info_i++ ;
        }
    }
}


// �}�l�樫
void Maze::Walk( ) {
    int x = 0, y = 0 ;
    record_path_i = 0 ;
    passed_goal = 0 ;
    while ( goal > 0 ) {
        if ( Choice_path( x, y ) == 1 ) {  // �V�k
            if ( record_path[record_path_i] != 0 ) record_path_i++ ;
            record_path[record_path_i] = 1 ;
            if ( chartPtr[x][y] != 'G' ) chartPtr[x][y] = 'V' ;  // �קK�~�NG��V
            while ( y + 1 < width && ( chartPtr[x][y+1] == 'E' || chartPtr[x][y+1] == 'G' ) ) {  // ���쩳
                y++ ;
                if ( chartPtr[x][y] == 'G' ) {
                    goal-- ;  // ����G�ؼд�@
                    passed_goal++ ;
                }
                else chartPtr[x][y] = 'V' ;
            }
        }
        else if ( Choice_path( x, y ) == 2 ) {  // �V�U
            if ( record_path[record_path_i] != 0 ) record_path_i++ ;
            record_path[record_path_i] = 2 ;
            if ( chartPtr[x][y] != 'G' ) chartPtr[x][y] = 'V' ;
            while ( x + 1 < length && ( chartPtr[x+1][y] == 'E' || chartPtr[x+1][y] == 'G' ) ) {
                x++ ;
                if ( chartPtr[x][y] == 'G' ) {
                    goal-- ;
                    passed_goal++ ;
                }
                else chartPtr[x][y] = 'V' ;
            }
        }
        else if ( Choice_path( x, y ) == 3 ) {  // �V��
            record_path_i++ ;
            record_path[record_path_i] = 3 ;
            if ( chartPtr[x][y] != 'G' ) chartPtr[x][y] = 'V' ;
            while ( y - 1 > -1 && ( chartPtr[x][y-1] == 'E' || chartPtr[x][y-1] == 'G' ) ) {
                y-- ;
                if ( chartPtr[x][y] == 'G' ) {
                    goal-- ;
                    passed_goal++ ;
                }
                else chartPtr[x][y] = 'V' ;
            }
        }
        else if ( Choice_path( x, y ) == 4 ) {  // �V�W
            record_path_i++ ;
            record_path[record_path_i] = 4 ;
            if ( chartPtr[x][y] != 'G' ) chartPtr[x][y] = 'V' ;
            while ( x - 1 > -1 && ( chartPtr[x-1][y] == 'E' || chartPtr[x-1][y] == 'G' ) ) {
                x-- ;
                if ( chartPtr[x][y] == 'G' ) {
                    goal-- ;
                    passed_goal++ ;
                }
                else chartPtr[x][y] = 'V' ;
            }
        }

        if ( Walk_break( x, y ) == 0 ) break ;  // �S�����F
    }

    Print_chart( chartPtr ) ;  // �L�X���L����m��
    if ( passed_goal > 0 ) {  // �P�_�O�_���g�L�ؼ�
        Draw_route( ) ;
        Print_chart( copy_chartPtr ) ;  // �L�X�i�檺���|
    }
}


// ��ܸ��|
int Maze::Choice_path( int x, int y ) {
    if ( y + 1 < width && record_path[record_path_i] != 3 ) {  // �קK�P�_�W�X�g�c, �åB���ਫ�P�̪�@������V�ۦP
        if ( chartPtr[x][y+1] == 'E' || chartPtr[x][y+1] == 'G' ) return 1 ;  // �k
    }

    if ( x + 1 < length && record_path[record_path_i] != 4 ) {
        if ( chartPtr[x+1][y] == 'E' || chartPtr[x+1][y] == 'G' ) return 2 ;  // �U
    }

    if ( y - 1 > -1 && record_path[record_path_i] != 1 ) {
        if ( chartPtr[x][y-1] == 'E' || chartPtr[x][y-1] == 'G' ) return 3 ;  // ��
    }

    if ( x - 1 > -1 && record_path[record_path_i] != 2 ) {
        if ( chartPtr[x-1][y] == 'E' || chartPtr[x-1][y] == 'G' ) return 4 ;  // �W
    }
}


// ��l��, ���}�C�Ҧ��������s
void Maze::Initialize_record_path( ) {
    for ( int i = 0 ; i < 30 ; i++ ) record_path[i] = 0 ;
}


// �P�_���쩳��|��O�_�٦���
int Maze::Walk_break( int x, int y ) {
    int boo = 0, direction ;
    direction = record_path[record_path_i] ;  // �ثe����V
    if ( Choice_path( x, y ) == 1 ) boo = 1 ;  // �k
    if ( Choice_path( x, y ) == 2 ) boo = 1 ;  // �U
    if ( Choice_path( x, y ) == 3 ) boo = 1 ;  // ��
    if ( Choice_path( x, y ) == 4 ) boo = 1 ;  // �W
    return boo ;  // 1������, 0�O�S����
}


// �L�X�g�c
void Maze::Print_chart( char ** ptr ) {
    for ( int i = 0 ; i < length ; i++ ) {
        for ( int j = 0 ; j < width ; j++ ) {
            printf( "%c ", ptr[i][j] ) ;
        }

        printf( "\n" ) ;
    }

    printf( "\n" ) ;
}


// �e�X���|
void Maze::Draw_route( ) {
    int x = 0, y = 0, i = 0, number ;
    number = passed_goal ;  // ���X�ӥؼЭn��
    while ( number > 0 ) {
        if ( record_path[i] == 1 ) {  // �V�k
            if ( copy_chartPtr[x][y] != 'G' ) copy_chartPtr[x][y] = 'R' ;
            while ( y + 1 < width && ( copy_chartPtr[x][y+1] == 'E' || copy_chartPtr[x][y+1] == 'G' ) ) {  // ���쩳
                y++ ;
                if ( copy_chartPtr[x][y] == 'G' ) {
                    number-- ;
                    if ( number == 0 ) break ;
                }
                else copy_chartPtr[x][y] = 'R' ;
            }
        }
        else if ( record_path[i] == 2 ) {  // �V�U
            if ( copy_chartPtr[x][y] != 'G' ) copy_chartPtr[x][y] = 'R' ;
            while ( x + 1 < length && ( copy_chartPtr[x+1][y] == 'E' || copy_chartPtr[x+1][y] == 'G' ) ) {
                x++ ;
                if ( copy_chartPtr[x][y] == 'G' ) {
                    number-- ;
                    if ( number == 0 ) break ;
                }
                else copy_chartPtr[x][y] = 'R' ;
            }
        }
        else if ( record_path[i] == 3 ) {  // �V��
            if ( copy_chartPtr[x][y] != 'G' ) copy_chartPtr[x][y] = 'R' ;
            while ( y - 1 > -1 && ( copy_chartPtr[x][y-1] == 'E' || copy_chartPtr[x][y-1] == 'G' ) ) {
                y-- ;
                if ( copy_chartPtr[x][y] == 'G' ) {
                    number-- ;
                    if ( number == 0 ) break ;
                }
                else copy_chartPtr[x][y] = 'R' ;
            }
        }
        else if ( record_path[i] == 4 ) {  // �V�W
            if ( copy_chartPtr[x][y] != 'G' ) copy_chartPtr[x][y] = 'R' ;
            while ( x - 1 > -1 && ( copy_chartPtr[x-1][y] == 'E' || copy_chartPtr[x-1][y] == 'G' ) ) {
                x-- ;
                if ( copy_chartPtr[x][y] == 'G' ) {
                    number-- ;
                    if ( number == 0 ) break ;
                }
                else copy_chartPtr[x][y] = 'R' ;
            }
        }

        if ( i == record_path_i ) break ;  // ��ܤw�g�৹�Ҧ���V�F
        i++ ;  // �U�@�Ӥ�V
    }
}


// �P�_�ɦW�O�_���[�W.txt
bool Detect_txt( char name[50] ) {
    int name_l = strlen( name ) ;
    if ( name[name_l - 1] == 't' && name[name_l - 2] == 'x' && name[name_l - 3] == 't' &&
         name[name_l - 4] == '.' ) return true ;
    return false ;
}


// �D�{��
int main( void ) {
    while ( true ) {  // ���ư���
        FILE * fptr ;  // �ŧi�@�Ӥ�����
        char file_name[50] ;
        bool have_txt = false ;
        Maze m ;  // �ŧi�@�Ӱg�c���O����H
        int error = 0 ;  // �x�s���~��T

        printf( "\nHow many goals you want to go ? : " ) ;
        scanf( "%d", &m.goal ) ;
        if ( m.goal == 0 ) {  // �P�_��J�O�_���Ʀr
            printf( "\nPlease enter a number, and it must be greater than zero !\n" ) ;
            printf( "\nPlease re-execute !\n" ) ;
            return 1 ;  // �Lreturn���ܵ{���|��, �u�୫�s�sĶ
        }

        printf( "\nPlease make sure your executable file, program and test data are in the same folder !\n" ) ;
        printf( "\nEnter your file ( remember add \".txt\" behind file's name ) : " ) ;
        scanf( "%s", file_name ) ;
        printf( "\n" ) ;
        fptr = fopen( file_name, "r" ) ;  // ���}���, �B�]���u��Ū����󤺮e
        fscanf( fptr, "%d", &m.width ) ;  // �q�ɮפ�Ū���榡�Ƽƾ�( ������, �nŪ���@�Ӿ��, �@�Ӿ���ܶq����} )
        fscanf( fptr, "%d", &m.length ) ;

        have_txt = Detect_txt( file_name ) ;  // �P�_�O�_���[.txt
        if ( have_txt == false ) {
            printf( "Please check your file's name and must have \".txt\" behind it !\n" ) ;
            error = 1 ;
        }
        else if ( fptr == NULL ) {
            printf( "Not find this file !\n" ) ;
            error = 1 ;
        }

        if ( error == 0 ) m.Access_data( fptr ) ;  // �S�����~, �B�z���
        else printf( "\nPlease try again !\n\n" ) ;

        fclose( fptr ) ;  // �������

        for ( int i = 0 ; i < m.length ; i++ ) {  // �������
            free( m.chartPtr[i] ) ;
            free( m.copy_chartPtr[i] ) ;
        }

        free( m.chartPtr ) ;
        free( m.copy_chartPtr ) ;
    }

    return 0 ;
}
