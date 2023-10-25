//11127134 �L���

#include <iostream> // C++�y�k(��J��X)
#include <fstream> // �]�t����J�y���Y���
#include <vector> // �s�g�c�G���ʺA�}�C
#include <utility> // �]�tstd::pair

using namespace std; // 

class Maze { // �x�s�g�c��ơA�~���{���n�z�L�����O����k��ܤ~��s���x�}���e
private: // �p���~�ӡA�u���Ө禡�~��s��
    int column; // �x�}����
    int row; // �x�}����
    vector<vector<char> > charArray; // �x�s�g�c�̭����r�Ť������ʺA�G���}�C
    vector<pair<int, int> > coordinates; // �ϥ�pair���x�s�y�й�
    int goals; // �Ѿl�ؼм�(�|�ܰ�)
    int shortlength; // �̵u���|��
public: // �ۥѡA�~���禡�]�����
    Maze () { // c++�y�k�����s�b���غc�l

    }

    Maze (Maze& aMaze) { // �ƻsprimate, Vector
        column = aMaze.column;
        row = aMaze.row;
        goals = aMaze.goals;
        charArray = aMaze.charArray;
    }

    bool load (string fileName) { // Ū���ɮר��x�s
        string completeFileName = "input" + string(fileName) + ".txt"; // �������W
        ifstream inputFile(completeFileName.c_str()); // �ϥ� C++ ������J�y
        if (!inputFile.is_open()) { // �p�G�ɮ׵L�k�Q���}
            cerr << completeFileName <<" does not exist!" << endl;
            return false;
        }

        column = 0; // �]�w�G���}�C���C��
        row = 0;    // �]�w�G���}�C�����
        inputFile >> column >> row; // �̧�Ū���ɮפ��e(int int)
        charArray.resize(row, vector<char>(column)); // �Ыؤ@�ӪŪ��G���r���V�q�A���t�G���r���}�C

        for (int i = 0; i < row; i++) { // Ū����󤺮e�æs�x��G���V�q
            for (int j = 0; j < column; j++) {
                inputFile >> charArray[i][j]; // Ū���ɮפ������x�}
            }
        }

        inputFile.close(); // �������
        return true;
    }
    
    bool findGoals(Maze& vMaze, char command, int direction, int i, int j) { // ���j���g�c�A�k�U���W�A�w�g���ؼЭӼ�
        if (command == '2') { // �u��command == '2'�ɭn��Jgoals�A�_�hgoals��=1
            cin >> goals; // ��Jgoals��
            while (goals < 0 || goals > 100 || goals == 0) {
                if (goals == 0 || goals > 100) {
                    cout << endl << "### The number must be in [1,100] ###" << endl;
                    cout << endl << "Number of G (goals): ";
                    cin >> goals;
                }
                if (goals < 0) {
                    cout << endl << "Number of G (goals): ";
                    cin >> goals;
                }
            }
        }
        else if (command == '1')  goals = 1;

        bool returnvalue = false; // ��findGoals���^�ǭ�

        command = '0'; // ����j�ɦA�]�@���W���A���j�u�]�U��!!!
        //charArray[i][j]; i��row-1(��), j��column-1

        int goalsvalue = 0; // �x�s���j�e��goals��
        // �p�Greturn�쥪�W���A���W�����k��M�U���������F�A�N��S�����ؼи��|
        if (i == 0 && j == 0 && vMaze.charArray[0][1] != 'E' && vMaze.charArray[1][0] != 'E')  return false;
        if (vMaze.charArray[i][j] == 'E') { // ���쪺�r��=E
            vMaze.charArray[i][j] = 'V'; // ��E�令V
            if (direction == 1) { // ���k
                if (j + 1 < column) { // ���b�̥k
                    goalsvalue = goals; // �������j�e��goals��
                    returnvalue = findGoals(vMaze, command, 1, i, j+1); // ����Ӫ���V��(�k)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (returnvalue == true)  return true; // �����ؼ�
                }
                if (i + 1 < row) { // ���b�̤U
                    goalsvalue = goals; // �������j�e��goals��
                    returnvalue = findGoals(vMaze, command, 2, i+1, j); // ���ܤ�V��(�U)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (returnvalue == true)  return true; // �����ؼ�
                }
                if (i > 0) { // ���b�̤W
                    goalsvalue = goals; // �������j�e��goals��
                    returnvalue = findGoals(vMaze, command, 4, i-1, j); // ���ܤ�V��(�W)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (returnvalue == true)  return true; // �����ؼ�
                }
                return false; // ���L�k�e�i�N��h
            }
            if (direction == 2) { // ���U
                if (i + 1 < row) { // ���b�̤U
                    goalsvalue = goals; // �������j�e��goals��
                    returnvalue = findGoals(vMaze, command, 2, i+1, j); // ����Ӫ���V��(�U)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (returnvalue == true)  return true; // �����ؼ�
                }
                if (j > 0) { // ���b�̥�
                    goalsvalue = goals; // �������j�e��goals��
                    returnvalue = findGoals(vMaze, command, 3, i, j-1); // ���ܤ�V��(��)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (returnvalue == true)  return true; // �����ؼ�
                }
                if (j + 1 < column) { // ���b�̥k
                    goalsvalue = goals; // �������j�e��goals��
                    returnvalue = findGoals(vMaze, command, 1, i, j+1); // ���ܤ�V��(�k)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (returnvalue == true)  return true; // �����ؼ�
                }
                return false; // ���L�k�e�i�N��h
            }
            if (direction == 3) { // ����
                if (j > 0) { // ���b�̥�
                    goalsvalue = goals; // �������j�e��goals��
                    returnvalue = findGoals(vMaze, command, 3, i, j-1); // ����Ӫ���V��(��)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (returnvalue == true)  return true; // �����ؼ�
                }
                if (i > 0) { // ���b�̤W
                    goalsvalue = goals; // �������j�e��goals��
                    returnvalue = findGoals(vMaze, command, 4, i-1, j); // ���ܤ�V��(�W)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (returnvalue == true)  return true; // �����ؼ�
                }
                if (i + 1 < row) { // ���b�̤U
                    goalsvalue = goals; // �������j�e��goals��
                    returnvalue = findGoals(vMaze, command, 2, i+1, j); // ���ܤ�V��(�U)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (returnvalue == true)  return true; // �����ؼ�
                }
                return false; // ���L�k�e�i�N��h
            }
            else { // ���W
                if (i > 0) { // ���b�̤W
                    goalsvalue = goals; // �������j�e��goals��
                    returnvalue = findGoals(vMaze, command, 4, i-1, j); // ����Ӫ���V��(�W)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (returnvalue == true)  return true; // �����ؼ�
                }
                if (j + 1 < column) { // ���b�̥k
                    goalsvalue = goals; // �������j�e��goals��
                    returnvalue = findGoals(vMaze, command, 1, i, j+1); // ���ܤ�V��(�k)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (returnvalue == true)  return true; // �����ؼ�
                }
                if (j > 0) { // ���b�̥�
                    goalsvalue = goals; // �������j�e��goals��
                    returnvalue = findGoals(vMaze, command, 3, i, j-1); // ���ܤ�V��(��)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (returnvalue == true)  return true; // �����ؼ�
                }
                return false; // ���L�k�e�i�N��h
            }
        }
        else if (vMaze.charArray[i][j] == 'G') { // ���P�_G���S�����L(�O�_�bcoordinates���s�b)�A�p�G���s�b�A�K�[�y�Ш�coordinates
            // �p�G�y��G�s�b�~��(����L��V)
            if (coordinates.empty()) { // �x�sG���y�а}�C�O�Ū�
                coordinates.push_back(make_pair(i, j)); // �N���y�вK�[���x�sG���y�а}�C
                goals--; // ���G���ܡA�ؼФ�1
                if (goals == 0) { // �p�G�ؼЧ䧹�F
                    return true;
                }
                else { // �٨S�����~�򩹭��V��
                    if (direction == 1) { // ���k
                        if (j + 1 < column) { // ���b�̥k
                            returnvalue = findGoals(vMaze, command, 1, i, j+1); // ����Ӫ���V��(�k)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        if (i + 1 < row) { // ���b�̤U
                            returnvalue = findGoals(vMaze, command, 2, i+1, j); // ���ܤ�V��(�U)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        if (i > 0) { // ���b�̤W
                            returnvalue = findGoals(vMaze, command, 4, i-1, j); // ���ܤ�V��(�W)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        return false; // ���L�k�e�i�N��h
                    }
                    if (direction == 2) { // ���U
                        if (i + 1 < row) { // ���b�̤U
                            returnvalue = findGoals(vMaze, command, 2, i+1, j); // ����Ӫ���V��(�U)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        if (j > 0) { // ���b�̥�
                            returnvalue = findGoals(vMaze, command, 3, i, j-1); // ���ܤ�V��(��)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        if (j + 1 < column) { // ���b�̥k
                            returnvalue = findGoals(vMaze, command, 1, i, j+1); // ���ܤ�V��(�k)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        return false; // ���L�k�e�i�N��h
                    }
                    if (direction == 3) { // ����
                        if (j > 0) { // ���b�̥�
                            returnvalue = findGoals(vMaze, command, 3, i, j-1); // ����Ӫ���V��(��)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        if (i > 0) { // ���b�̤W
                            returnvalue = findGoals(vMaze, command, 4, i-1, j); // ���ܤ�V��(�W)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        if (i + 1 < row) { // ���b�̤U
                            returnvalue = findGoals(vMaze, command, 2, i+1, j); // ���ܤ�V��(�U)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        return false; // ���L�k�e�i�N��h
                    }
                    else { // ���W
                        if (i > 0) { // ���b�̤W
                            returnvalue = findGoals(vMaze, command, 4, i-1, j); // ����Ӫ���V��(�W)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        if (j + 1 < column) { // ���b�̥k
                            returnvalue = findGoals(vMaze, command, 1, i, j+1); // ���ܤ�V��(�k)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        if (j > 0) { // ���b�̥�
                            returnvalue = findGoals(vMaze, command, 3, i, j-1); // ���ܤ�V��(��)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        return false; // ���L�k�e�i�N��h
                    }
                }
            }
            else { // �ϥ�for�j���ˬd�O�_�w�s�b�y��
                bool exist = false; // �w�]���s�b
                for (int k = 0; k < coordinates.size(); k++) { // �j�Mcoordinates�}�C���Ҧ������A�ݦs���s�b�P�ثeG�ۦP���y��
                    if (coordinates[k].first == i && coordinates[k].second == j) { // �p�G�y�ЬۦP
                        exist = true; // �]���s�b
                    }
                }
                if (exist == true) { // �ME�ާ@�ۦP�A�u�O���Χ令V
                    if (direction == 1) { // ���k
                        if (j + 1 < column) { // ���b�̥k
                            returnvalue = findGoals(vMaze, command, 1, i, j+1); // ����Ӫ���V��(�k)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        if (i + 1 < row) { // ���b�̤U
                            returnvalue = findGoals(vMaze, command, 2, i+1, j); // ���ܤ�V��(�U)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        if (i > 0) { // ���b�̤W
                            returnvalue = findGoals(vMaze, command, 4, i-1, j); // ���ܤ�V��(�W)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        return false; // ���L�k�e�i�N��h
                    }
                    if (direction == 2) { // ���U
                        if (i + 1 < row) { // ���b�̤U
                            returnvalue = findGoals(vMaze, command, 2, i+1, j); // ����Ӫ���V��(�U)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        if (j > 0) { // ���b�̥�
                            returnvalue = findGoals(vMaze, command, 3, i, j-1); // ���ܤ�V��(��)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        if (j + 1 < column) { // ���b�̥k
                            returnvalue = findGoals(vMaze, command, 1, i, j+1); // ���ܤ�V��(�k)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        return false; // ���L�k�e�i�N��h
                    }
                    if (direction == 3) { // ����
                        if (j > 0) { // ���b�̥�
                            returnvalue = findGoals(vMaze, command, 3, i, j-1); // ����Ӫ���V��(��)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        if (i > 0) { // ���b�̤W
                            returnvalue = findGoals(vMaze, command, 4, i-1, j); // ���ܤ�V��(�W)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        if (i + 1 < row) { // ���b�̤U
                            returnvalue = findGoals(vMaze, command, 2, i+1, j); // ���ܤ�V��(�U)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        return false; // ���L�k�e�i�N��h
                    }
                    else { // ���W
                        if (i > 0) { // ���b�̤W
                            returnvalue = findGoals(vMaze, command, 4, i-1, j); // ����Ӫ���V��(�W)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        if (j + 1 < column) { // ���b�̥k
                            returnvalue = findGoals(vMaze, command, 1, i, j+1); // ���ܤ�V��(�k)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        if (j > 0) { // ���b�̥�
                            returnvalue = findGoals(vMaze, command, 3, i, j-1); // ���ܤ�V��(��)
                            if (returnvalue == true)  return true; // �����ؼ�
                        }
                        return false; // ���L�k�e�i�N��h
                    }
                }
                else { // ���P�_G���S�����L(�O�_�bcoordinates���s�b)�A�p�G���s�b�A�K�[�y�Ш�coordinates
                    // �p�G�y��G�s�b�~��(����L��V)
                    coordinates.push_back(make_pair(i, j)); // �N���y�вK�[���x�sG���y�а}�C
                    goals--; // ���G���ܡA�ؼФ�1
                    if (goals == 0) { // �p�G�ؼЧ䧹�F
                        return true;
                    }
                    else { // �٨S�����~�򩹭��V��
                        if (direction == 1) { // ���k
                            if (j + 1 < column) { // ���b�̥k
                                returnvalue = findGoals(vMaze, command, 1, i, j+1); // ����Ӫ���V��(�k)
                                if (returnvalue == true)  return true; // �����ؼ�
                            }
                            if (i + 1 < row) { // ���b�̤U
                                returnvalue = findGoals(vMaze, command, 2, i+1, j); // ���ܤ�V��(�U)
                                if (returnvalue == true)  return true; // �����ؼ�
                            }
                            if (i > 0) { // ���b�̤W
                                returnvalue = findGoals(vMaze, command, 4, i-1, j); // ���ܤ�V��(�W)
                                if (returnvalue == true)  return true; // �����ؼ�
                            }
                            return false; // ���L�k�e�i�N��h
                        }
                        if (direction == 2) { // ���U
                            if (i + 1 < row) { // ���b�̤U
                                returnvalue = findGoals(vMaze, command, 2, i+1, j); // ����Ӫ���V��(�U)
                                if (returnvalue == true)  return true; // �����ؼ�
                            }
                            if (j > 0) { // ���b�̥�
                                returnvalue = findGoals(vMaze, command, 3, i, j-1); // ���ܤ�V��(��)
                                if (returnvalue == true)  return true; // �����ؼ�
                            }
                            if (j + 1 < column) { // ���b�̥k
                                returnvalue = findGoals(vMaze, command, 1, i, j+1); // ���ܤ�V��(�k)
                                if (returnvalue == true)  return true; // �����ؼ�
                            }
                            return false; // ���L�k�e�i�N��h
                        }
                        if (direction == 3) { // ����
                            if (j > 0) { // ���b�̥�
                                returnvalue = findGoals(vMaze, command, 3, i, j-1); // ����Ӫ���V��(��)
                                if (returnvalue == true)  return true; // �����ؼ�
                            }
                            if (i > 0) { // ���b�̤W
                                returnvalue = findGoals(vMaze, command, 4, i-1, j); // ���ܤ�V��(�W)
                                if (returnvalue == true)  return true; // �����ؼ�
                            }
                            if (i + 1 < row) { // ���b�̤U
                                returnvalue = findGoals(vMaze, command, 2, i+1, j); // ���ܤ�V��(�U)
                                if (returnvalue == true)  return true; // �����ؼ�
                            }
                            return false; // ���L�k�e�i�N��h
                        }
                        else { // ���W
                            if (i > 0) { // ���b�̤W
                                returnvalue = findGoals(vMaze, command, 4, i-1, j); // ����Ӫ���V��(�W)
                                if (returnvalue == true)  return true; // �����ؼ�
                            }
                            if (j + 1 < column) { // ���b�̥k
                                returnvalue = findGoals(vMaze, command, 1, i, j+1); // ���ܤ�V��(�k)
                                if (returnvalue == true)  return true; // �����ؼ�
                            }
                            if (j > 0) { // ���b�̥�
                                returnvalue = findGoals(vMaze, command, 3, i, j-1); // ���ܤ�V��(��)
                                if (returnvalue == true)  return true; // �����ؼ�
                            }
                            return false; // ���L�k�e�i�N��h
                        }
                    }
                }
            }
        }
        else  return false; // �p�G���OE�MG���ܴN��^
    }
    
    bool findshortpath(Maze& vMaze, Maze& tMaze, char command, int direction, int i, int j, int length) { // ���j���g�c�A�k�U���W�A�w�g���ؼЭӼ�
        if (length > row * column)  return false; // ���ਫ�W�L�Ҧ��������`�X���
        if (command == '3')  goals = 1; // �u��@��G

        command = '0'; // ����j�ɦA�]�@���W���A���j�u�]�U��!!!   //charArray[i][j]; i��row-1(��), j��column-1

        int goalsvalue = 0; // �x�s���j�e��goals��

        bool returnvalue = false; // �P�_tempreturn���^�ǭ�
        bool tempreturn = false; // �쥻���x�}(���|��)

        if (goals < 1) { // �ܤ֧��@��G�F
            if (length == shortlength)  return false; // �����W�@�Ӹ��|�����٭n��
        }

        if (tMaze.charArray[i][j] == 'E') { // ���쪺�r��=E
            vMaze.charArray[i][j] = 'V'; // ��E�令V
            if (direction == 1) { // ���k
                if (j + 1 < column) { // ���b�̥k
                    goalsvalue = goals; // �������j�e��goals��
                    tempreturn = findshortpath(vMaze, tMaze, command, 1, i, j+1, length+1); // ����Ӫ���V��(�k)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (tempreturn == true)  returnvalue = true; // findshortpath�^�ǭȡA���ઽ��return true or false
                }
                if (i + 1 < row) { // ���b�̤U
                    goalsvalue = goals; // �������j�e��goals��
                    tempreturn = findshortpath(vMaze, tMaze, command, 2, i+1, j, length+1); // ���ܤ�V��(�U)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (tempreturn == true)  returnvalue = true; // findshortpath�^�ǭȡA���ઽ��return true or false
                }
                if (i > 0) { // ���b�̤W
                    goalsvalue = goals; // �������j�e��goals��
                    tempreturn = findshortpath(vMaze, tMaze, command, 4, i-1, j, length+1); // ���ܤ�V��(�W)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (tempreturn == true)  returnvalue = true; // findshortpath�^�ǭȡA���ઽ��return true or false
                }
                return returnvalue; // �ѤU�T��V�����~�^��true,false�A�������n�g�L
            }
            if (direction == 2) { // ���U
                if (i + 1 < row) { // ���b�̤U
                    goalsvalue = goals; // �������j�e��goals��
                    tempreturn = findshortpath(vMaze, tMaze, command, 2, i+1, j, length+1); // ����Ӫ���V��(�U)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (tempreturn == true)  returnvalue = true; // findshortpath�^�ǭȡA���ઽ��return true or false
                }
                if (j > 0) { // ���b�̥�
                    goalsvalue = goals; // �������j�e��goals��
                    tempreturn = findshortpath(vMaze, tMaze, command, 3, i, j-1, length+1); // ���ܤ�V��(��)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (tempreturn == true)  returnvalue = true; // findshortpath�^�ǭȡA���ઽ��return true or false
                }
                if (j + 1 < column) { // ���b�̥k
                    goalsvalue = goals; // �������j�e��goals��
                    tempreturn = findshortpath(vMaze, tMaze, command, 1, i, j+1, length+1); // ���ܤ�V��(�k)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (tempreturn == true)  returnvalue = true; // findshortpath�^�ǭȡA���ઽ��return true or false
                }
                return returnvalue; // �ѤU�T��V�����~�^��true,false�A�������n�g�L
            }
            if (direction == 3) { // ����
                if (j > 0) { // ���b�̥�
                    goalsvalue = goals; // �������j�e��goals��
                    tempreturn = findshortpath(vMaze, tMaze, command, 3, i, j-1, length+1); // ����Ӫ���V��(��)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (tempreturn == true)  returnvalue = true; // findshortpath�^�ǭȡA���ઽ��return true or false
                }
                if (i > 0) { // ���b�̤W
                    goalsvalue = goals; // �������j�e��goals��
                    tempreturn = findshortpath(vMaze, tMaze, command, 4, i-1, j, length+1); // ���ܤ�V��(�W)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (tempreturn == true)  returnvalue = true; // findshortpath�^�ǭȡA���ઽ��return true or false
                }
                if (i + 1 < row) { // ���b�̤U
                    goalsvalue = goals; // �������j�e��goals��
                    tempreturn = findshortpath(vMaze, tMaze, command, 2, i+1, j, length+1); // ���ܤ�V��(�U)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (tempreturn == true)  returnvalue = true; // findshortpath�^�ǭȡA���ઽ��return true or false
                }
                return returnvalue; // �ѤU�T��V�����~�^��true,false�A�������n�g�L
            }
            else { // ���W
                if (i > 0) { // ���b�̤W
                    goalsvalue = goals; // �������j�e��goals��
                    tempreturn = findshortpath(vMaze, tMaze, command, 4, i-1, j, length+1); // ����Ӫ���V��(�W)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (tempreturn == true)  returnvalue = true; // findshortpath�^�ǭȡA���ઽ��return true or false
                }
                if (j + 1 < column) { // ���b�̥k
                    goalsvalue = goals; // �������j�e��goals��
                    tempreturn = findshortpath(vMaze, tMaze, command, 1, i, j+1, length+1); // ���ܤ�V��(�k)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (tempreturn == true)  returnvalue = true; // findshortpath�^�ǭȡA���ઽ��return true or false
                }
                if (j > 0) { // ���b�̥�
                    goalsvalue = goals; // �������j�e��goals��
                    tempreturn = findshortpath(vMaze, tMaze, command, 3, i, j-1, length+1); // ���ܤ�V��(��)
                    if (goalsvalue > goals)  charArray[i][j] = 'R'; // �p�G���j�e�ȸ��j�A�N�����G�Areturn�ɭn�令R
                    if (tempreturn == true)  returnvalue = true; // findshortpath�^�ǭȡA���ઽ��return true or false
                }
                return returnvalue; // �ѤU�T��V�����~�^��true,false�A�������n�g�L
            }
        }
        else if (vMaze.charArray[i][j] == 'G') { // ���G�����������שMreturn true�^�ӵeR�A�A�~��a�^��G������סA�p�G��u�л\�x�}
            goals--; // ���G���ܡA�ؼФ�1
            if (coordinates.empty()) { // �x�sG���y�а}�C�O�Ū�
                coordinates.push_back(make_pair(i, j)); // �N���y�вK�[���x�sG���y�а}�C
                shortlength = length; // �̵u���|����
                return true;
            }
            else { // �ϥ�for�j���ˬd�O�_�w�s�b�y��
                bool exist = false; // �w�]���s�b
                for (int k = 0; k < coordinates.size(); k++) { // �j�Mcoordinates�}�C���Ҧ������A�ݦs���s�b�P�ثeG�ۦP���y��
                    if (coordinates[k].first == i && coordinates[k].second == j) { // �p�G�y�ЬۦP
                        exist = true; // �]���s�b
                    }
                }
                if (exist == true) { // �ME�ާ@�ۦP�A�u�O���Χ令V
                    if (shortlength > length) { // �s���|�������|���u
                        shortlength = length; // �N�s���|������л\������|��
                        for (int i = 0; i < row; i++) { // �N��Ӫ�R�x�}���m���@�}�l�g�c���ˤl
                            for (int j = 0; j < column; j++) {
                                charArray[i][j] = tMaze.charArray[i][j];
                            }
                        }
                        return true;
                    }
                    else  return false;
                }
                else { // ���P�_G���S�����L(�O�_�bcoordinates���s�b)�A�p�G���s�b�A�K�[�y�Ш�coordinates
                    coordinates.push_back(make_pair(i, j)); // �N���y�вK�[���x�sG���y�а}�C
                    if (shortlength > length) { // �s���|�������|���u
                        shortlength = length; // �N�s���|������л\������|��
                        for (int i = 0; i < row; i++) { // �N��Ӫ�R�x�}���m���@�}�l�g�c���ˤl
                            for (int j = 0; j < column; j++) {
                                charArray[i][j] = tMaze.charArray[i][j];
                            }
                        }
                        return true;
                    }
                    else  return false;
                }
            }
        }
        else  return false; // �p�G���OE�MG���ܴN��^
    }

    void show() { // �N�g�c�L�X��
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                cout << charArray[i][j];
            }
            cout << endl;
        }
        cout << endl;
        return;
    }

    void shortpath() {
        if (goals == 1)  cout << endl << "### There is no path to find a goal! ###" << endl; // goals�����S�ܤ�(�S���)
        else  cout << endl << "Shortest path length = " << shortlength << endl; // ��X�̵u���|
    }

    void clr() { // �N�g�c�����M��
        charArray.clear(); // �M�Űg�c�̪��Ҧ�����
        charArray.resize(0, vector<char>(column)); // �����M��
        return;
    }
};

int main(void) {
    char command = '0'; // user command
    int direction = 1; // �w�]�e�i��V���k��
    int i = 0; // ����g�c���y�ФW�U���ʡA(�����U�A�t���W)
    int j = 0; // ����g�c���y�Х��k���ʡA(�����k�A�t����)
    int length = 1; // ���|����

    do {
        Maze aMaze; // a matrix
        string fileName; // a file name

        cout << endl << "*** Path Finding ***";
        cout << endl << "* 0. Quit          *";
        cout << endl << "* 1. One goal      *";
        cout << endl << "* 2. More goals    *";
        cout << endl << "********************";
        cout << endl << "Input a command(0, 1, 2, 3): ";

        cin >> command; // get the command
        if ((command == '1')||(command == '2')||(command == '3')) { // command='1'��'2'��'3'�ɤ~����R�O
            cout << endl << "Input a file number: ";
            cin >> fileName; // Ū�J�ɮצW��(�Ʀr)
            if (command == '2')  cout << endl << "Number of G (goals): ";
            if (aMaze.load(fileName)) { // load the original matrix
                Maze vMaze(aMaze); // a copy to keep the visited cells
                if ((command == '1')||(command == '2')) {
                    bool success = aMaze.findGoals(vMaze, command, direction, i, j); // find a path to goal(s)
                    vMaze.show(); // show on screen the visited cells
                    if (success) // to check if the goal is reached or not
                        aMaze.show(); // show on screen the route to reach the goal
                }
                else if ((command == '3')) {
                    Maze tMaze(aMaze); // a copy to keep the temped cells
                    bool havefind = aMaze.findshortpath(vMaze, tMaze, command, direction, i, j, length); // find a path to goal(s)
                    vMaze.show(); // show on screen the visited cells
                    if (havefind) // to check if the goal is reached or not
                        aMaze.show(); // show on screen the route to reach the goal
                    aMaze.shortpath(); // �L�̵u���|
                    tMaze.clr(); // clear up the copy
                }
                vMaze.clr(); // clear up the copy
            } // end inner-if
            aMaze.clr(); // clear up the original matrix
        } // end outer-if 
        else if (command == '0')  break; // '0': stop the program
        else  cout << endl << "Command does not exist!" << endl;
        system("pause"); // pause the execution
    }while(true);
    system("pause"); // pause the execution
    return 0;
} // end of main