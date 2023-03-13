#include "mainwindow.h"
#include "QImage"
#include "QLabel"
#include <QApplication>
#include <iostream>
#include <vector>

using namespace std;

//void printMatrix(QImage Matrix)
//{
//    for (int i = 0; i < Matrix.size(); i++)
//    {
//        for (int j = 0; j < Matrix[i].size(); j++)
//        {
//            printf("%4i", Matrix[i][j]);
//        }
//        printf("\n");
//    }
//    printf("\n\n");
//}

auto calculateMatrixHadamardRows(QImage dstImage, int rows)
{
    int n;
    int tmp1, tmp2;
    int count = (int)log2(rows);
    //int count = 1;
    for (int i = 0; i < count; i++)
    {
        n =(int) pow(2, i);
        for (int k = 0; k < dstImage.width(); k++)
        {
            for (int j = 0; j < dstImage.height(); j +=(int) pow(2, i + 1))
            {
                for (int h = 0; h < n; h++)
                {
                    tmp1 = (dstImage.pixel(j+h,k) + dstImage.pixel(j + h + n,k));
                    auto alpha_tmp1 = QColor(tmp1).alpha();
                    //printf("%4i", QColor(tmp1).black());
                    tmp2 = (dstImage.pixel(j + h,k) - dstImage.pixel(j + h + n,k));
                    auto alpha_tmp2 = QColor(tmp2).alpha();
                    dstImage.setPixelColor(j + h,k, qAlpha(alpha_tmp1));
                    dstImage.setPixelColor(j + n + h,k,qAlpha(alpha_tmp2));
                    //cout<<qGray(tmp1)<<endl;
                }
            }
        }
    }
    return dstImage;
}

auto calculateMatrixHadamardColumns(QImage dstImage, int columns)
{
    int n;
    int tmp1, tmp2;
    int count = (int)log2(columns);
    //int count = 1;
    for (int i = 0; i < count; i++)
    {
        n = (int)pow(2, i);
        for (int j = 0; j < dstImage.height(); j += (int)pow(2, i + 1))
        {
            for (int k = 0; k < dstImage.width(); k++)
            {
                for (int h = 0; h < n; h++)
                {
                    tmp1 = (dstImage.pixel(k,j + h) + dstImage.pixel(k,j + h + n));
                    tmp2 = (dstImage.pixel(k,j + h) - dstImage.pixel(k,j + h + n));
                    //cout<<A.pixelColor(j + h, k)<<endl;
                    auto black_tmp1 = QColor(tmp1).black();
                    //cout<<QColor(tmp1).red()<<endl;
                    auto black_tmp2 = QColor(tmp2).black();
                    dstImage.setPixelColor(k,j + h, qGray(black_tmp1));
                    dstImage.setPixelColor(k,j+n+h,qGray(black_tmp2));
                    //A.setPixel(k,j + h,tmp1);
                    //A.setPixel(k,j + n + h,tmp2);
                }
            }
        }
    }
    return dstImage;
}

//auto calculateMatrixHadamardColumns(QImage A, int columns)
//{
//    int n;
//    int tmp1, tmp2;
//    int count = (int)log2(columns);
//    //int count = 1;
//    for (int i = 0; i < count; i++)
//    {
//        n = (int)pow(2, i);
//        for (int j = 0; j < A.width(); j += (int)pow(2, i + 1))
//        {
//            for (int k = 0; k < A.height(); k++)
//            {
//                for (int h = 0; h < n; h++)
//                {
//                    tmp1 = (A.pixel(k,j + h) + A.pixel(k,j + h + n))/2;
//                    tmp2 = (A.pixel(k,j + h) - A.pixel(k,j + h + n))/2;
//                    //cout<<A.pixelColor(j + h, k)<<endl;
//                    auto red_tmp1 = QColor(tmp1).red();
//                    auto green_tmp1 = QColor(tmp1).green();
//                    auto blue_tmp1 = QColor(tmp1).blue();
//                    //cout<<QColor(tmp1).red()<<endl;
//                    auto red_tmp2 = QColor(tmp2).red();
//                    auto green_tmp2 = QColor(tmp2).green();
//                    auto blue_tmp2 = QColor(tmp2).blue();
//                    A.setPixelColor(k,j + h, qRgb(red_tmp1, green_tmp1, blue_tmp1));
//                    A.setPixelColor(k,j+n+h,qRgb(red_tmp2, green_tmp2, blue_tmp2));
//                    //A.setPixel(k,j + h,tmp1);
//                    //A.setPixel(k,j + n + h,tmp2);
//                }
//            }
//        }
//    }
//    return A;
//}

//auto reverseCalculateMatrixHadamardRows(QImage A, int rows)
//{
//    int n;
//    int tmp1, tmp2;
//    int count = (int)log2(rows);
//    for (int i = 0; i < count; i++)
//    {
//        n = (int)pow(2, i);
//        for (int k = 0; k < A.height(); k++)
//        {
//            for (int j = 0; j < A.width(); j += (int)pow(2, i + 1))
//            {
//                for (int h = 0; h < n; h++)
//                {
//                    tmp1 = (A.pixel(j + h,k) - A.pixel(j + h + n,k));
//                    //cout<<A.pixelColor(j + h, k)<<endl;
//                    auto red_tmp1 = QColor(tmp1).red();
//                    auto green_tmp1 = QColor(tmp1).green();
//                    auto blue_tmp1 = QColor(tmp1).blue();
//                    //cout<<QColor(tmp1).red()<<endl;
//                    tmp2 = (A.pixel(j + h,k) + A.pixel(j + h + n,k));
//                    auto red_tmp2 = QColor(tmp2).red();
//                    auto green_tmp2 = QColor(tmp2).green();
//                    auto blue_tmp2 = QColor(tmp2).blue();
//                    A.setPixelColor(j + h,k, qRgb(red_tmp2, green_tmp2, blue_tmp2));
//                    A.setPixelColor(j + n + h,k,qRgb(red_tmp1, green_tmp1, blue_tmp1));
////                    tmp1 = (A.pixel(j + h,k) - A.pixel(j + h + n,k));
////                    tmp2 = (A.pixel(j + h,k) + A.pixel(j + h + n,k));
////                    A.setPixel(j + h,k,tmp2);
////                    A.setPixel(j + n + h,k,tmp1);
//                }
//            }
//        }
//    }
//    return A;
//}

auto reverseCalculateMatrixHadamardRows(QImage dstImage, int rows)
{
    int n;
    int tmp1, tmp2;
    int count = (int)log2(rows);
    for (int i = 0; i < count; i++)
    {
        n = (int)pow(2, i);
        for (int k = 0; k < dstImage.width(); k++)
        {
            for (int j = 0; j < dstImage.height(); j += (int)pow(2, i + 1))
            {
                for (int h = 0; h < n; h++)
                {
                    tmp1 = (dstImage.pixel(j + h,k) + dstImage.pixel(j + h + n,k))/2;
                    //cout<<A.pixelColor(j + h, k)<<endl;
                    auto black_tmp1 = QColor(tmp1).black();
                    //auto white_tmp1 = QColor(tmp1).white();
                    //cout<<QColor(tmp1).red()<<endl;
                    tmp2 = (dstImage.pixel(j + h,k) - dstImage.pixel(j + h + n,k))/2;
                    auto black_tmp2 = QColor(tmp2).black();
                    //auto white_tmp2 = QColor(tmp2).white();
                    dstImage.setPixelColor(j + h,k, qGray(black_tmp1));
                    dstImage.setPixelColor(j + n + h,k,qGray(black_tmp2));
//                    tmp1 = (A.pixel(j + h,k) - A.pixel(j + h + n,k));
//                    tmp2 = (A.pixel(j + h,k) + A.pixel(j + h + n,k));
//                    A.setPixel(j + h,k,tmp2);
//                    A.setPixel(j + n + h,k,tmp1);
                }
            }
        }
    }
    return dstImage;
}

auto reverseCalculateMatrixHadamardColumns(QImage A, int columns)
{
    int n;
    int tmp1, tmp2;
    int count = (int)log2(columns);
    for (int i = 0; i < count; i++)
    {
        n = (int)pow(2, i);
        for (int j = 0; j < A.width(); j += (int)pow(2, i + 1))
        {
            for (int k = 0; k < A.height(); k++)
            {
                for (int h = 0; h < n; h++)
                {
                    tmp1 = (A.pixel(k,j + h) + A.pixel(k,j + h + n))/2;
                    tmp2 = (A.pixel(k,j + h) - A.pixel(k,j + h + n))/2;
                    //tmp1 = A.pixel(j + h,k) + A.pixel(j + h + n,k);
                    //cout<<A.pixelColor(j + h, k)<<endl;
                    auto black_tmp1 = QColor(tmp1).black();
                    //cout<<QColor(tmp1).red()<<endl;
                    //tmp2 = A.pixel(j + h,k) - A.pixel(j + h + n,k);
                    auto black_tmp2 = QColor(tmp2).black();
                    A.setPixelColor(k,j + h, qGray(black_tmp1));
                    A.setPixelColor(k,j + n + h,qGray(black_tmp2));
                    //A.setPixel(k,j + h,tmp1);
                    //A.setPixel(k,j + n + h,tmp2);
//                    tmp1 = (A.pixel(k,j + h) - A.pixel(k,j + h + n)) / 2;
//                    tmp2 = (A.pixel(k,j + h) + A.pixel(k,j + h + n)) / 2;
//                    A.setPixel(k,j + h,tmp2);
//                    A.setPixel(k,j + n + h,tmp1);
                }
            }
        }
    }
    return A;
}

int binaryToDecimal(int n)
{
    int num = n;
    int dec_value = 0;

    int base = 1;

    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;

        dec_value += last_digit * base;

        base = base * 2;
    }

    return dec_value;
}

int from_decimal_to_binary_and_revert(int num, int razryad)
{
    std::vector<int> temp(razryad);
    std::vector<int> result(razryad);
    for( int i = 0; i<(int) temp.size(); i++)
    {
        temp[i] = 0;
        result[i] = 0;
    }
    int t=0, d=1;
    while(num)
    {
        t +=(num%2)*d;
        num=num/2;
        d=d*10; // razryad
    }
    int n=10;
    for(int i = 0; i<(int) temp.size(); i++)
    {
        temp[i] = t%n;
        t/=10;
    }
    for(int i = 0; i< (int) temp.size(); i++)
    {
        result[i] = temp[i];
    }
    //std::reverse(std::begin(result), std::end(result));
    int num_res = 0;
    int degree = pow(10, razryad - 1);
    for(int i = 0; i< razryad; i++)
    {
        num_res+=degree*result[i];
        degree/=10;
    }
    int res = binaryToDecimal(num_res);
    return res;
}

std::vector < std::vector <int> > swapPeliMatrix(std::vector < std::vector <int> >& A, int rows)
{
    std::vector < std::vector <int> > result(rows, std::vector <int>(A[0].size()));
    for (int i = 0; i < (int) A.size(); i++)
    {
        for (int j = 0; j < (int) A[i].size(); j++)
        {
                result[from_decimal_to_binary_and_revert(i, (int)log2(rows))][j] = A[i][j];
        }
    }
    return result;
}

std::vector < std::vector <int> > swapPeliMatrixColumns(std::vector < std::vector <int> >& B, int columns)
{
    std::vector < std::vector <int> > result(columns, std::vector <int>(B[0].size()));
    for (int j = 0; j < (int) B.size(); j++)
    {
        for (int i = 0; i < (int) B[j].size(); i++)
        {
                result[i][from_decimal_to_binary_and_revert(j, (int)log2(columns))] = B[i][j];
        }
    }
    return result;
}

std::vector < std::vector <int> > reverseSwapPeliMatrix(std::vector < std::vector <int> >& C, int rows)
{
    std::vector < std::vector <int> > result(rows, std::vector <int>(C[0].size()));
    for (int i = 0; i < (int) C.size(); i++)
    {
        for (int j = 0; j < (int) C[i].size(); j++)
        {
                result[from_decimal_to_binary_and_revert(i, (int)log2(rows))][j] = C[i][j];
        }
    }
    return result;
}

std::vector < std::vector <int> > reverseSwapPeliMatrixColumns(std::vector < std::vector <int> >& D, int columns)
{
    std::vector < std::vector <int> > result(columns, std::vector <int>(D[0].size()));
    for (int j = 0; j < (int) D.size(); j++)
    {
        for (int i = 0; i < (int) D[j].size(); i++)
        {
                result[i][from_decimal_to_binary_and_revert(j, (int)log2(columns))] = D[i][j];
        }
    }
    return result;
}

void calculateMatrixPeliRows(std::vector < std::vector <int> >& B, int rows)
{
    int n;
    int tmp1, tmp2;
    int count = (int)log2(rows);
    for (int i = 0; i < count; i++)
    {
        n = (int)pow(2, i);
        for (int j = 0; j < (int) B.size(); j += (int)pow(2, i + 1))
        {
            for (int k = 0; k < (int) B[j].size(); k++)
            {
              for (int h = 0; h < n; h++)
                {
                    tmp1 = B[j + h][k] + B[j + h + n][k];
                    tmp2 = B[j + h][k] - B[j + h + n][k];
                    B[j + h][k] = tmp1;
                    B[j + n + h][k] = tmp2;
                }
            }
        }
        //printMatrix(B);
    }
}

void calculateMatrixPeliColumns(std::vector < std::vector <int> >& B, int columns)
{
    int n;
    int tmp1, tmp2;
    int count = (int)log2(columns);
    for (int i = 0; i < count; i++)
    {
        n = (int)pow(2, i);
        for (int j = 0; j < (int) B.size(); j += (int)pow(2, i + 1))
        {
            for (int k = 0; k < (int) B[j].size(); k++)
            {
              for (int h = 0; h < n; h++)
                {
                    tmp1 = B[k][j + h] + B[k][j + h + n];
                    tmp2 = B[k][j + h] - B[k][j + h + n];
                    B[k][j + h] = tmp1;
                    B[k][j + n + h] = tmp2;
                }
            }
        }
        //printMatrix(B);
    }
}

void reverseCalculateMatrixPeliRows(std::vector < std::vector <int> >& B, int rows)
{
    int n;
    int tmp1, tmp2;
    int count = (int)log2(rows);
    for (int i = 0; i < count; i++)
    {
        n = (int)pow(2, i);
        for (int j = 0; j < (int) B.size(); j += (int)pow(2, i + 1))
        {
            for (int k = 0; k < (int) B[j].size(); k++)
            {
                for (int h = 0; h < n; h++)
                {
                    tmp1 = (B[j + h][k] - B[j + h + n][k])/2;
                    tmp2 = (B[j + h][k] + B[j + h + n][k])/2;
                    B[j + h][k] = tmp2;
                    B[j + n + h][k] = tmp1;
                }
            }
        }
        //printMatrix(B);
    }
}

void reverseCalculateMatrixPeliColumns(std::vector < std::vector <int> >& B, int columns)
{
    int n;
    int tmp1, tmp2;
    int count = (int)log2(columns);
    for (int i = 0; i < count; i++)
    {
        n = (int)pow(2, i);
        for (int j = 0; j < (int) B[0].size(); j += (int)pow(2, i + 1))
        {
            for (int k = 0; k < (int) B[j].size(); k++)
            {
                for (int h = 0; h < n; h++)
                {
                    tmp1 = (B[k][j + h] - B[k][j + h + n]) / 2;
                    tmp2 = (B[k][j + h] + B[k][j + h + n]) / 2;
                    B[k][j + h] = tmp2;
                    B[k][j + n + h] = tmp1;
                }
            }
        }
        //printMatrix(B);
    }
}

QImage convertToGrayScale(const QImage &srcImage)
{
    QImage dstImage = srcImage.convertToFormat(srcImage.hasAlphaChannel()?
            QImage::Format_ARGB32 : QImage::Format_RGB32);

    unsigned int *data = (unsigned int*)dstImage.bits();
    int pixelCount = dstImage.width()*dstImage.height();
    for (int i = 0; i < pixelCount; ++i)
    {
        int val = qGray(*data);
        *data = qRgba(val, val, val, qAlpha(*data));
        ++data;
    }
    return dstImage;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QImage image("D:/Gauss.png");
    image.save("start.png");
    cout<<image.width()<<image.height()<<endl;
    convertToGrayScale(image);
    QImage result_convertToGrayScale = convertToGrayScale(image);
    result_convertToGrayScale.save("result_convertToGrayScale.png");
    QImage result_calculateMatrixHadamardRows = calculateMatrixHadamardRows(result_convertToGrayScale, image.height());
    QImage result_calculateMatrixHadamardColumns = calculateMatrixHadamardColumns(result_calculateMatrixHadamardRows, image.width());
//    QImage result_calculateMatrixHadamardColumns = calculateMatrixHadamardColumns(result_calculateMatrixHadamardRows, result_calculateMatrixHadamardRows.width());
    QImage result_reverseCalculateMatrixHadamardRows = reverseCalculateMatrixHadamardRows(result_calculateMatrixHadamardColumns, result_calculateMatrixHadamardColumns.height());
    QImage result_reverseCalculateMatrixHadamardColumns = reverseCalculateMatrixHadamardColumns(result_reverseCalculateMatrixHadamardRows, result_reverseCalculateMatrixHadamardRows.width());
//    QImage result_calculateMatrixHadamardRows2 = calculateMatrixHadamardRows(result_calculateMatrixHadamardColumns, result_calculateMatrixHadamardColumns.height());
//    QImage result_calculateMatrixHadamardColumns2 = calculateMatrixHadamardColumns(result_calculateMatrixHadamardRows2, result_calculateMatrixHadamardRows2.width());
//    QImage result_calculateMatrixHadamardRows3 = calculateMatrixHadamardRows(result_calculateMatrixHadamardColumns2, result_calculateMatrixHadamardColumns2.height());
//    QImage result_calculateMatrixHadamardColumns3 = calculateMatrixHadamardColumns(result_calculateMatrixHadamardRows3, result_calculateMatrixHadamardRows3.width());
//    QImage result_calculateMatrixHadamardRows4 = calculateMatrixHadamardRows(result_calculateMatrixHadamardColumns3, result_calculateMatrixHadamardColumns3.height());
//    QImage result_calculateMatrixHadamardColumns4 = calculateMatrixHadamardColumns(result_calculateMatrixHadamardRows4, result_calculateMatrixHadamardRows4.width());
//    QImage result_calculateMatrixHadamardRows5 = calculateMatrixHadamardRows(result_calculateMatrixHadamardColumns4, result_calculateMatrixHadamardColumns4.height());
//    QImage result_calculateMatrixHadamardColumns5 = calculateMatrixHadamardColumns(result_calculateMatrixHadamardRows5, result_calculateMatrixHadamardRows5.width());
//    QImage result_calculateMatrixHadamardRows6 = calculateMatrixHadamardRows(result_calculateMatrixHadamardColumns5, result_calculateMatrixHadamardColumns5.height());
//    QImage result_calculateMatrixHadamardColumns6 = calculateMatrixHadamardColumns(result_calculateMatrixHadamardRows6, result_calculateMatrixHadamardRows6.width());
//    QImage result_calculateMatrixHadamardRows7 = calculateMatrixHadamardRows(result_calculateMatrixHadamardColumns6, result_calculateMatrixHadamardColumns6.height());
//    QImage result_calculateMatrixHadamardColumns7 = calculateMatrixHadamardColumns(result_calculateMatrixHadamardRows7, result_calculateMatrixHadamardRows7.width());
    //QImage result_reverseCalculateMatrixHadamardRows = reverseCalculateMatrixHadamardRows(result_calculateMatrixHadamardColumns, result_calculateMatrixHadamardColumns.height());
    //QImage result_reverseCalculateMatrixHadamardColumns = reverseCalculateMatrixHadamardColumns(result_reverseCalculateMatrixHadamardRows, result_reverseCalculateMatrixHadamardRows.width());
    //QPicture pic;
    //QPainter paint(&pic);
    //paint.drawImage(0,0,im);
//    for (int i = 0; i < image.width(); i++) {
//                for (int j = 0; j < image.height(); j++) {
//                    //image.setPixel(i, j, qRgb(0, 0, 0));

//                }
//            }
    QLabel myLabel;
    result_calculateMatrixHadamardRows.save("result_calculateMatrixHadamardRows1.png");
    result_calculateMatrixHadamardColumns.save("result_calculateMatrixHadamardColumns1.png");
    result_reverseCalculateMatrixHadamardColumns.save("result_reverseCalculateMatrixHadamardColumns2.png");
    result_reverseCalculateMatrixHadamardRows.save("result_reverseCalculateMatrixHadamardRows2.png");
//    result_calculateMatrixHadamardRows2.save("result_calculateMatrixHadamardRows2.png");
//    result_calculateMatrixHadamardColumns2.save("result_calculateMatrixHadamardColumns2.png");
//    result_calculateMatrixHadamardRows3.save("result_calculateMatrixHadamardRows3.png");
//    result_calculateMatrixHadamardColumns3.save("result_calculateMatrixHadamardColumns3.png");
//    result_calculateMatrixHadamardRows4.save("result_calculateMatrixHadamardRows4.png");
//    result_calculateMatrixHadamardColumns4.save("result_calculateMatrixHadamardColumns4.png");
//    result_calculateMatrixHadamardRows5.save("result_calculateMatrixHadamardRows5.png");
//    result_calculateMatrixHadamardColumns5.save("result_calculateMatrixHadamardColumns5.png");
//    result_calculateMatrixHadamardRows6.save("result_calculateMatrixHadamardRows6.png");
//    result_calculateMatrixHadamardColumns6.save("result_calculateMatrixHadamardColumns6.png");
//    result_calculateMatrixHadamardRows7.save("result_calculateMatrixHadamardRows7.png");
//    result_calculateMatrixHadamardColumns7.save("result_calculateMatrixHadamardColumns7.png");
    //result_reverseCalculateMatrixHadamardRows.save("result_reverseCalculateMatrixHadamardRows.png");
    //result_reverseCalculateMatrixHadamardColumns.save("result_reverseCalculateMatrixHadamardColumns.png");
    myLabel.setPixmap(QPixmap::fromImage(image));
    //myLabel.show();
    //w.show();
    return a.exec();
}
