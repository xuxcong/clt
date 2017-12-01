#include "tokamak.h"
#include <cstdio>
#include <petscvec.h>
#include <petscmat.h>
#include <petscksp.h>
#define int PetscInt
#define float PetscScalar

Tokamak::Tokamak() {
	MPI_Comm_size(PETSC_COMM_WORLD, &size);
	MPI_Comm_rank(PETSC_COMM_WORLD, &rank);
	//后面加入许多接口配置
	step = 100;
	r_size = 111;
	t_size = 200;
	p_size = 8;
	gather = new float***[10];
	//申请动态内存
	if (rank == 0) {
		for (int i = 0; i < 10; i++) {
			gather[i] = new float**[r_size];
			for (int j = 0; j < r_size; j++) {
				gather[i][j] = new float*[t_size];
				for (int k = 0; k < t_size; k++)
					gather[i][j][k] = new float[p_size];
			}
		}
		b_r		= gather[0];
		b_t		= gather[1];
		b_p		= gather[2];
		v_r		= gather[3];
		v_t		= gather[4];
		v_p		= gather[5];
		pres	= gather[6];
		dens	= gather[7];
		toco_r	= gather[8];
		toco_p	= gather[9];
	}
	else
		for (int i = 0; i < 10; i++)
			gather[i] = NULL;
}

void Tokamak::readin() {
	//从文件中读入磁场、速度、压强、密度的环坐标数据
	if (rank != 0)
		return;
	char data_file_path[] = "./data/";
	char *data_file_name[] = {"Br_nova.dat", "Bt_nova.dat", "Bp_nova.dat", \
							  "vr_nova.dat", "vt_nova.dat", "vp_nova.dat", \
							  "P_nova.dat", "rho_nova.dat"};
	for (int i = 0; i < 8; i++) {
		//获得文件完整路径名并打开文件
		char *file_path_name = new char[strlen(data_file_path) + strlen(data_file_name[i])+1];
		file_path_name[0] = 0;
		strcat(file_path_name, data_file_path);
		strcat(file_path_name, data_file_name[i]);
		//printf("%s\n", file_path_name);
		FILE *fpr = fopen(file_path_name, "r");
		//开始读取文件
		for (int j = 0; j < r_size; j++) {
			for (int k = 0; k < t_size; k++) {
				for (int u = 0; u < p_size; u++) {
					fscanf(fpr, "%lf", &gather[i][j][k][u]);
					//printf("%d %d %d %d : %e\n", i, j, k, u, gather[i][j][k][u]);
				}
			}
		}
	}
}

void Tokamak::switch2Grid(){
	//四个环坐标变四个网格
}

void Tokamak::calculateDeltaTime() {
	//计算隐格式时间步长
}

void Tokamak::makeMatrixVec() {
	//由四个网格组装成一个矩阵和右端项
}

void Tokamak::calculate() {
	//计算出下一个时间步的结果
}

void Tokamak::scatterVec() {
	//将计算结果还原为四个网格
}

void Tokamak::switch2Cyc() {
	//转换为环坐标
}

void Tokamak::extraPolation() {
	//向外插值
}

void Tokamak::print() {
	//输出
}