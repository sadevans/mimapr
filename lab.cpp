#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

constexpr int x1 = 0;
constexpr int x2 = 12;

constexpr double q1 = 10;
constexpr double q2 = 0;
constexpr double q3 = 4;
constexpr double q4 = -17;

constexpr int u_border1 = 4;
constexpr int u_border2 = 2;

int mat_size(int n, int rank)
{
	return n * rank - (n - 1);
}

MatrixXd assemble(int size, int rank, MatrixXd K)
{
	MatrixXd res = MatrixXd::Zero(mat_size(size, rank), mat_size(size, rank));
	int msize = mat_size(size, rank);
	for(int i = 0; i < msize - 1; i += rank - 1)
		res(seqN(i, rank), seqN(i, rank)) += K;

	/* border conditions */
	res(0, 0) = 1;
	for(int i = 1; i <= rank; i++)
		res(0, i) = 0;

	return res;
}

VectorXd assemble_vec(int size, int rank, MatrixXd F)
{
	MatrixXd res = MatrixXd::Zero(mat_size(size, rank), 1);
	for(int i = 0; i < mat_size(size, rank) - 1; i += rank - 1)
		for(int j = 0; j < rank; j++)
			res(i + j, 0) += F(j, 0);
	/* derivative border conditions */
	res(0) = u_border1;
	/* simple border conditions */
	res(mat_size(size, rank) - 1) -= q1 * u_border2;
	return res;
}

double analytic_func(double x)
{
	double c1 = -0.25, c2 = 11.1725714802124;
	return c2*sin(sqrt(2.0/5.0)*x) + c1*cos(sqrt(2.0/5.0)*x) + 17.0/4.0;
}

void solve(MatrixXd K, MatrixXd F, int rank, int n, bool compare)
{
	MatrixXd K_full = assemble(n, rank, K);
	MatrixXd F_full = assemble_vec(n, rank, F);
	double L = (double)(x2 - x1) / n;
	MatrixXd solution = K_full.partialPivLu().solve(F_full);
	for(int i = 0; i < mat_size(n, rank); i++)
	{
		double x = x1 + (double)i * L / (rank - 1);
		double y = compare ? abs(analytic_func(x) - solution(i)) : solution(i);
		std::cout << x << '\t' << y << '\n';
	}
}

void solve_linear(int rank, int n, bool compare)
{
	double L = (double)(x2 - x1) / n;
	Matrix2d K{
		{L*q3/3 - q2/2 - q1/L, L*q3/6 + q2/2 + q1/L},
		{L*q3/6 - q2/2 + q1/L, L*q3/3 + q2/2 - q1/L}
	};
	Vector2d F{
		{-L*q4/2},
		{-L*q4/2}
	};
	solve(K, F, rank, n, compare);
}

void solve_cubic(int rank, int n, bool compare)
{
	double L = (double)(x2 - x1) / n;
	MatrixXd K4{
		{
			8*L*q3/105 - q2/2 - 37*q1/(10*L),
			33*L*q3/560 + 57*q2/80 + 189*q1/(40*L),
			-3*L*q3/140 - 3*q2/10 - 27*q1/(20*L),
			19*L*q3/1680 + 7*q2/80 + 13*q1/(40*L)
		},
		{
			33*L*q3/560 - 57*q2/80 + 189*q1/(40*L),
			27*L*q3/70 - 54*q1/(5*L),
			-27*L*q3/560 + 81*q2/80 + 297*q1/(40*L),
			-3*L*q3/140 - 3*q2/10 - 27*q1/(20*L)
		}, 
		{-
			3*L*q3/140 + 3*q2/10 - 27*q1/(20*L),
			-27*L*q3/560 - 81*q2/80 + 297*q1/(40*L),
			27*L*q3/70 - 54*q1/(5*L),
			33*L*q3/560 + 57*q2/80 + 189*q1/(40*L)
		}, 
		{
			19*L*q3/1680 - 7*q2/80 + 13*q1/(40*L),
			-3*L*q3/140 + 3*q2/10 - 27*q1/(20*L),
			33*L*q3/560 - 57*q2/80 + 189*q1/(40*L),
			8*L*q3/105 + q2/2 - 37*q1/(10*L)
		}
	};
	VectorXd F4{
		{-L*q4/8}, 
		{-3*L*q4/8}, 
		{-3*L*q4/8}, 
		{-L*q4/8}
	};
	solve(K4, F4, rank, n, compare);
}

int main(int argc, char **argv)
{
	int rank = 2;
	int n = 20;
	bool compare = false;
	if(argc > 1 && std::string(argv[1]) == "--cubic")
		rank = 4;
	else if(argc > 1 && std::string(argv[1]) == "--linear")
		rank = 2;
	if(argc > 3 && std::string(argv[2]) == "-n")
		n = atoi(argv[3]);
	if(argc > 4 && std::string(argv[4]) == "--compare")
		compare = true;
		
	if(rank == 2)
		solve_linear(rank, n, compare);
	else if(rank == 4)
		solve_cubic(rank, n, compare);

    return 0;
}
