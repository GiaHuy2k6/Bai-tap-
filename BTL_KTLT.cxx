#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Cấu trúc sinh viên
typedef struct SinhVien {
    char mssv[10];
    char ten[50];
    float gpa;
    struct SinhVien* next;
} SV;
// Thêm sinh viên vào đầu danh sách
SV* themSV(SV* ds, char* mssv, char* ten, float gpa) {
    SV* sv = (SV*)malloc(sizeof(SV));
    strcpy(sv->mssv, mssv);
    strcpy(sv->ten, ten);
    sv->gpa = gpa;
    sv->next = ds;
    return sv;
}
// Thêm sinh viên vào cuối danh sách
SV* themSVVaoCuoi(SV* ds, char* mssv, char* ten, float gpa) {
    SV* sv = (SV*)malloc(sizeof(SV));
    strcpy(sv->mssv, mssv);
    strcpy(sv->ten, ten);
    sv->gpa = gpa;
    sv->next = NULL;

    if (ds == NULL) return sv;

    SV* p = ds;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = sv;
    return ds;
}
// Hiển thị danh sách sinh viên
void hienThi(SV* ds) {
    if (ds == NULL) {
        printf("Danh sach trong!\n");
        return;
    }
    printf("\nMSSV\t\tTen\t\tGPA\n");
    printf("----------------------------------------\n");
    for (SV* p = ds; p != NULL; p = p->next) {
        printf("%s\t%-15s\t%.2f\n", p->mssv, p->ten, p->gpa);
    }
}
// Tìm sinh viên theo MSSV
SV* timSV(SV* ds, char* mssv) {
    for (SV* p = ds; p != NULL; p = p->next) {
        if (strcmp(p->mssv, mssv) == 0) {
            return p;
        }
    }
    return NULL;
}
// Xóa sinh viên theo MSSV
SV* xoaSV(SV* ds, char* mssv) {
    SV *p = ds, *truoc = NULL;
    while (p != NULL && strcmp(p->mssv, mssv) != 0) {
        truoc = p;
        p = p->next;
    }
    if (p == NULL) {
        printf("Khong tim thay sinh vien co MSSV %s\n", mssv);
        return ds;
    }
    if (truoc == NULL) { // Xóa đầu danh sách
        SV* temp = ds->next;
        free(ds);
        ds = temp;
    } else {
        truoc->next = p->next;
        free(p);
    }
    printf("Da xoa sinh vien co MSSV %s\n", mssv);
    return ds;
}
// Sắp xếp danh sách theo GPA giảm dần
void sapXepTheoGPA(SV* ds) {
    for (SV* p = ds; p != NULL; p = p->next) {
        for (SV* q = p->next; q != NULL; q = q->next) {
            if (p->gpa < q->gpa) {
                char tempTen[50], tempMSSV[10];
                float tempGPA;

                strcpy(tempTen, p->ten);
                strcpy(tempMSSV, p->mssv);
                tempGPA = p->gpa;

                strcpy(p->ten, q->ten);
                strcpy(p->mssv, q->mssv);
                p->gpa = q->gpa;

                strcpy(q->ten, tempTen);
                strcpy(q->mssv, tempMSSV);
                q->gpa = tempGPA;
            }
        }
    }
    printf("Da sap xep danh sach theo GPA giam dan.\n");
}
// Ghi danh sách ra file
void ghiFile(SV* ds, const char* tenFile) {
    FILE* f = fopen(tenFile, "w");
    if (!f) {
        printf("Khong mo duoc file!\n");
        return;
        }
    for (SV* p = ds; p != NULL; p = p->next) {
        fprintf(f, "%s;%s;%.2f\n", p->mssv, p->ten, p->gpa);
    }
    fclose(f);
    printf("Da ghi danh sach vao file '%s'\n", tenFile);
}
// Đọc danh sách từ file
SV* docFile(const char* tenFile) {
    FILE* f = fopen(tenFile, "r");
    if (!f) {
        printf("Khong mo duoc file!\n");
        return NULL;
    }
    SV* ds = NULL;
    char line[100];
    while (fgets(line, sizeof(line), f)) {
        char mssv[10], ten[50];
        float gpa;
        sscanf(line, "%[^;];%[^;];%f", mssv, ten, &gpa);
        ds = themSVVaoCuoi(ds, mssv, ten, gpa);
    }
    fclose(f);
    printf("Da doc danh sach tu file '%s'\n", tenFile);
    return ds;
}
// Giải phóng bộ nhớ danh sách
void giaiPhong(SV* ds) {
    SV* p;
    while (ds != NULL) {
        p = ds;
        ds = ds->next;
        free(p);
    }
}
// Menu chương trình
void menu() {
    printf("\n====== QUAN LY SINH VIEN ======\n");
    printf("1. Them sinh vien\n");
    printf("2. Hien thi danh sach\n");
    printf("3. Tim sinh vien theo MSSV\n");
    printf("4. Xoa sinh vien theo MSSV\n");
    printf("5. Sap xep danh sach theo GPA\n");
    printf("6. Ghi danh sach ra file\n");
    printf("7. Doc danh sach tu file\n");
    printf("0. Thoat\n");
    printf("Lua chon cua ban: ");
}
int main() {
    SV* ds = NULL;
    int chon;
    char mssv[10], ten[50];
    float gpa;

    do {
        menu();
        scanf("%d", &chon);
        getchar(); // Xóa bộ đệm

        switch (chon) {
            case 1:
                printf("Nhap MSSV: ");
                fgets(mssv, sizeof(mssv), stdin);
                mssv[strcspn(mssv, "\n")] = 0;

                if (timSV(ds, mssv) != NULL) {
                    printf("MSSV da ton tai, khong the them.\n");
                    break;
                }

                printf("Nhap ten: ");
                fgets(ten, sizeof(ten), stdin);
                ten[strcspn(ten, "\n")] = 0;

                do {
                    printf("Nhap GPA (0.0 - 4.0): ");
                    scanf("%f", &gpa);
                    getchar();
                    if (gpa < 0 || gpa > 4) {
                        printf("GPA khong hop le, vui long nhap lai!\n");
                    }
                } while (gpa < 0 || gpa > 4);

                ds = themSV(ds, mssv, ten, gpa);
                printf("Da them sinh vien.\n");
                break;

            case 2:
                hienThi(ds);
                break;

            case 3:
                printf("Nhap MSSV can tim: ");
                fgets(mssv, sizeof(mssv), stdin);
                mssv[strcspn(mssv, "\n")] = 0;

                {
                    SV* sv = timSV(ds, mssv);
                    if (sv != NULL) {
                        printf("Tim thay sinh vien: MSSV=%s, Ten=%s, GPA=%.2f\n", sv->mssv, sv->ten, sv->gpa);
                    } else {
                        printf("Khong tim thay sinh vien co MSSV %s\n", mssv);
                    }
                    }
                break;

            case 4:
                printf("Nhap MSSV can xoa: ");
                fgets(mssv, sizeof(mssv), stdin);
                mssv[strcspn(mssv, "\n")] = 0;

                ds = xoaSV(ds, mssv);
                break;

            case 5:
                sapXepTheoGPA(ds);
                break;

            case 6:
                ghiFile(ds, "sinhvien.txt");
                break;

            case 7:
                giaiPhong(ds);
                ds = docFile("sinhvien.txt");
                break;

            case 0:
                giaiPhong(ds);
                printf("Thoat chuong trinh.\n");
                break;

            default:
                printf("Lua chon khong hop le, vui long chon lai!\n");
        }
    } while (chon != 0);

    return 0;
}