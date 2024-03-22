#include "../include/long_numbers.h"
using namespace std;
const int com = 105;
namespace long_numb {
    class number {
    public:
        int exp = 0, sgn = 1;
        vector <int> mantis;

        friend bool operator==(const number &A, const number &B) {
            return A.sgn == B.sgn && A.exp == B.exp && A.mantis == B.mantis;
        }

        friend bool operator<(const number &A, const number &B) {
            if (A.sgn < B.sgn) {
                return true;
            }

            if (A.sgn == 1) {
                return A.exp < B.exp || (A.exp == B.exp && A.mantis < B.mantis);
            }

            return A.exp > B.exp || (A.exp == B.exp && A.mantis > B.mantis);
        }

        friend bool operator>(const number &A, const number &B) {
            return !(A == B || A < B);
        }

        friend bool operator!=(const number &A, const number &B) {
            return !(A == B);
        }

        friend number operator+(const number & A, const number & B) {
            number C;
            C.mantis.resize(com);
            C.exp = max(A.exp, B.exp);
            int a = C.exp - A.exp;
            int b = C.exp - B.exp;

            for (int i = 0; i + b < com; i++) {
                C.mantis[i + b] += B.mantis[i] * B.sgn;
            }

            for (int i = 0; i + a < com; i++) {
                C.mantis[i + a] += A.mantis[i] * A.sgn;
            }

            int sign = 1;
            for (int i = 0; i < com; i++) {
                if (C.mantis[i] > 0) {
                    break;
                }

                if (C.mantis[i] < 0) {
                    sign = -1;
                    break;
                }
            }

            for (int i = 0; i < com; i++) {
                C.mantis[i] *= sign;
            }

            for (int i = com - 1; i > 0; i--) {
                if (C.mantis[i] >= 10) {
                    C.mantis[i-1]++;
                    C.mantis[i] -= 10;
                }

                if (C.mantis[i] < 0) {
                    C.mantis[i-1]--;
                    C.mantis[i] += 10;
                }
            }

            if (C.mantis[0] >= 10){
                C.exp++;
                int val = C.mantis[0] % 10;
                C.mantis[0] /= 10;
                for (int i = 1; i < com; i++) {
                    swap(val, C.mantis[i]);
                }
            }

            if (!C.mantis[0]) {
                bool flag = false;
                for (int i = 0; i < com; i++) {
                    if (C.mantis[i]) {
                        flag = true;
                        break;
                    }
                }

                while (!C.mantis[0] && flag) {
                    C.exp--;
                    for (int i = 0; i + 1 < com; i++) {
                        swap(C.mantis[i], C.mantis[i + 1]);
                    }
                }

                if (!C.mantis[0]) {
                    C.exp = -1e6;
                }
            }

            C.sgn = sign;
            return C;
        }

        friend number operator-(const number & A, const number & B) {
            number X = B;
            X.sgn *= -1;
            return A + X;
        }

        friend number operator*(const number & A, const number & B) {
            number C, P = B, Q = A;
            C.mantis.resize(com);
            C.sgn = A.sgn * B.sgn;
            P.exp = B.exp + A.exp - com + 1;
            C.exp = P.exp;
            for (int i = com - 1; i >= 0; i--) {
                while (Q.mantis[i] > 0) {
                    Q.mantis[i]--;
                    C = C + P;
                }
                P.exp++;
            }

            if (!C.mantis[0]) {
                bool flag = false;
                for (int i = 0; i < com; i++) {
                    if (C.mantis[i]) {
                        flag = true;
                        break;
                    }
                }

                while (!C.mantis[0] && flag) {
                    C.exp--;
                    for (int i = 0; i + 1 < com; i++) {
                        swap(C.mantis[i], C.mantis[i + 1]);
                    }
                }

                if (!C.mantis[0]) {
                    C.exp = -1e6;
                }
            }

            return C;
        }

        friend number operator/(const number & A, const number & B) {
            number C;
            C.mantis.resize(com);
            C.exp = A.exp - B.exp;

            number A_abs = A, B_abs = B;
            A_abs.sgn = 1;
            B_abs.sgn = 1;
            B_abs.exp = A.exp;
            for (int i = 0; i < com; i++) {
                while (!(B_abs > A_abs) && C.mantis[i] < 10) {
                    C.mantis[i]++;
                    A_abs = A_abs - B_abs;
                }
                B_abs.exp--;
            }

            C.sgn = A.sgn * B.sgn;

            if (!C.mantis[0]) {
                bool flag = false;
                for (int i = 0; i < com; i++) {
                    if (C.mantis[i]) {
                        flag = true;
                        break;
                    }
                }

                while (!C.mantis[0] && flag) {
                    C.exp--;
                    for (int i = 0; i + 1 < com; i++) {
                        swap(C.mantis[i], C.mantis[i + 1]);
                    }
                }

                if (!C.mantis[0]) {
                    C.exp = -1e6;
                }
            }

            return C;
        }

        string to_string() {
            string ans;
            if (sgn == -1) {
                ans += '-';
            }

            if (exp < 0) {
                ans += '0';
                ans += '.';
                for (int i = exp + 1; i < 0; i++) {
                    ans += '0';
                }

                for (int i = 0; i < com; i++) {
                    ans += char(mantis[i] + '0');
                }
                return ans;
            }

            for (int i = 0; i <= min(exp, com - 1); i++) {
                ans += char(mantis[i] + '0');
            }

            ans += ".";
            for (int i = exp + 1; i < com; i++) {
                ans += char(mantis[i] + '0');
            }

            return ans;
        }

        friend number sqrt(const number & X) {
            number L, R = X, TWO;
            L.mantis.resize(com);
            TWO.mantis.resize(com);
            TWO.mantis[0] = 2;

            for (int i = 0; i < 334; i++) {
                number M = (L + R) / TWO;
                if (X < M*M) {
                    R = M;
                }
                else {
                    L = M;
                }
            }

            return L;
        }
    };
}

