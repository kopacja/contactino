/**
\file contres.cpp
CONTact RESidual
*/
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
#include <cfloat>
#include <algorithm>

#include "contactino.h"

/*! Evaluate shape functions and their 1st partial derivatives of 4-node bilinear element

\param r - 1st isoparametric (parent, reference) coordinate
\param s - 2nd isoparametric coordinate

\return H 1d array (4x1) of shape functions values
\return dH 2d array (4x2) of 1st partial derivatives of shape functions with respect to r (1st column) and s (2nd column)

*/
void sfd4(double* H, double* dH, double r, double s) {
  const double h1 = 0.25*(1-r)*(1-s);
  const double h2 = 0.25*(1+r)*(1-s);
  const double h3 = 0.25*(1+r)*(1+s);
  const double h4 = 0.25*(1-r)*(1+s);
  /***********************************************/
  const double h1r = -0.25*(1-s);
  const double h2r =  0.25*(1-s);
  const double h3r =  0.25*(s+1);
  const double h4r = -0.25*(1+s);
  /***********************************************/
  const double h1s =  0.25*(r-1);
  const double h2s = -0.25*(1+r);
  const double h3s =  0.25*(r+1);
  const double h4s =  0.25*(1-r);
  /***********************************************/
  H[0] = h1;
  H[1] = h2;
  H[2] = h3;
  H[3] = h4;

  dH[0] = h1r;
  dH[1] = h2r;
  dH[2] = h3r;
  dH[3] = h4r;

  dH[4] = h1s;
  dH[5] = h2s;
  dH[6] = h3s;
  dH[7] = h4s;
}

/*! Evaluate shape functions and their 1st partial derivatives of 8-node (serendipity) quadrilateral element

\param r - 1st isoparametric (parent, reference) coordinate
\param s - 2nd isoparametric coordinate

\return H 1d array (8x1) of shape functions values
\return dH 2d array (8x2) of 1st partial derivatives of shape functions with respect to r (1st column) and s (2nd column)

*/
void sfd8(double* H, double* dH, double r, double s) {
  const double h5 = 0.5*(1-r*r)*(1-s);
  const double h6 = 0.5*(1+r)*(1-s*s);
  const double h7 = 0.5*(1-r*r)*(1+s);
  const double h8 = 0.5*(1-r)*(1-s*s);

  const double h1 = 0.25*(1-r)*(1-s) - 0.5*h5 - 0.5*h8;
  const double h2 = 0.25*(1+r)*(1-s) - 0.5*h5 - 0.5*h6;
  const double h3 = 0.25*(1+r)*(1+s) - 0.5*h6 - 0.5*h7;
  const double h4 = 0.25*(1-r)*(1+s) - 0.5*h7 - 0.5*h8;

  /***********************************************/
  const double h5r = -r*(1-s);
  const double h6r = 0.5*(1-s*s);
  const double h7r = -r*(1+s);
  const double h8r = -0.5*(1-s*s);

  const double h1r = -0.25*(1-s) - 0.5*h5r - 0.5*h8r;
  const double h2r =  0.25*(1-s) - 0.5*h5r - 0.5*h6r;
  const double h3r =  0.25*(s+1) - 0.5*h6r - 0.5*h7r;
  const double h4r = -0.25*(1+s) - 0.5*h7r - 0.5*h8r;
  /***********************************************/
  const double h5s = -0.5*(1-r*r);
  const double h6s = -(1+r)*s;
  const double h7s = 0.5*(1-r*r);
  const double h8s = -(1-r)*s;

  const double h1s =  0.25*(r-1) - 0.5*h5s - 0.5*h8s;
  const double h2s = -0.25*(1+r) - 0.5*h5s - 0.5*h6s;
  const double h3s =  0.25*(r+1) - 0.5*h6s - 0.5*h7s;
  const double h4s =  0.25*(1-r) - 0.5*h7s - 0.5*h8s;
  /***********************************************/
  H[0] = h1;
  H[1] = h2;
  H[2] = h3;
  H[3] = h4;
  H[4] = h5;
  H[5] = h6;
  H[6] = h7;
  H[7] = h8;

  dH[0] = h1r;
  dH[1] = h2r;
  dH[2] = h3r;
  dH[3] = h4r;
  dH[4] = h5r;
  dH[5] = h6r;
  dH[6] = h7s;
  dH[7] = h8s;

  dH[8]  = h1s;
  dH[9]  = h2s;
  dH[10] = h3s;
  dH[11] = h4s;
  dH[12] = h5s;
  dH[13] = h6s;
  dH[14] = h7s;
  dH[15] = h8s;
}

/*! Evaluate shape functions and their 1st partial derivatives of 6-node (serendipity) triangular element

\param r - 1st isoparametric coordinate
\param s - 2nd isoparametric coordinate

\return H 1d array (6x1) of shape functions values
\return dH 2d array (6x2) of 1st partial derivatives of shape functions with respect to r (1st column) and s (2nd column)

*/
void sfd6(double* H, double* dH, double r, double s) {
  const double h4 = 4 * r*(1 - r - s);
  const double h5 = 4 * r*s;
  const double h6 = 4 * s*(1 - r - s);

  const double h1 = 1 - r - s - 0.5*h4 - 0.5*h6;
  const double h2 = r - 0.5*h4 - 0.5*h5;
  const double h3 = s - 0.5*h5 - 0.5*h6;
  /***********************************************/
  const double h4r = 4 * (1 - r - s) - 4 * r;
  const double h5r = 4 * s;
  const double h6r = -4 * s;

  const double h1r = -1 - 0.5*h4r - 0.5*h6r;
  const double h2r = 1 - 0.5*h4r - 0.5*h5r;
  const double h3r = 0 - 0.5*h5r - 0.5*h6r;
  /***********************************************/
  const double h4s = -4 * r;
  const double h5s = 4 * r;
  const double h6s = 4 * (1 - r - s) - 4 * s;

  const double h1s = -1 - 0.5*h4s - 0.5*h6s;
  const double h2s = 0 - 0.5*h4s - 0.5*h5s;
  const double h3s = 1 - 0.5*h5s - 0.5*h6s;
  /***********************************************/
  H[0] = h1;
  H[1] = h2;
  H[2] = h3;
  H[3] = h4;
  H[4] = h5;
  H[5] = h6;

  dH[0] = h1r;
  dH[1] = h2r;
  dH[2] = h3r;
  dH[3] = h4r;
  dH[4] = h5r;
  dH[5] = h6r;

  dH[6] = h1s;
  dH[7] = h2s;
  dH[8] = h3s;
  dH[9] = h4s;
  dH[10] = h5s;
  dH[11] = h6s;
}

/*! Evaluate shape functions and their 1st derivatives of 2-node bar element

\param r - 1st isoparametric coordinate

\return H 1d array (2x1) of shape functions values
\return dH 1d array (2x1) of 1st derivatives of shape functions with respect to r

*/
void sfd2(double* H, double* dH, double r) {
  const double h1 = 0.5*(1 - r);
  const double h2 = 0.5*(1 + r);
  /***********************************************/
  const double h1r = -0.5;
  const double h2r = 0.5;
  /***********************************************/
  H[0] = h1;
  H[1] = h2;

  dH[0] = h1r;
  dH[1] = h2r;
}

/*! Calculate contact residual term (gradient) and contact tangent term (Hessian)

\param len - maximal length of 1d arrays rows,cols, and vals
\param GPs - 2d array (GPs_len x ??? cols)
\param ISN - 2d array (nsn*)
\param IEN -
\param X -
\param U -
\param H -
\param dH -
\param gw -
\param activeGPsOld -
\param neq - Number of Equations
\param nsd - Number of Space Dimensions (usually 2 or 3)
\param npd - Number of Parametric Dimensions (usually 1 or 2) (parametric=reference=parent coordinates)
\param ngp - Number of GaussPoints on contact segment (segment means face of element)
\param nes - Number of Element Segments
\param nsn - Number of Segment Nodes
\param GPs_len - length of GPs array
\param epss - penalty parameter (usualy 100*Young's mudulus)
\param keyContactDetection - if is true, ...
\param keyAssembleKc - if is true, contact tangent term is assembled only

\return Gc - 1d array
\return rows - 1d array
\return cols - 1d array
\return valc - 1d array

*/
void assembleContactResidualAndStiffness(double* Gc_loc, double* Gc, double* Kc, double* vals, double* rows, double* cols, int* len, double* GPs, int* ISN, int* IEN, double* X, double* U, double* H, double* dH, double* gw, double* activeGPsOld, int neq, int nsd, int npd, int ngp, int nes, int nsn, int nen, int GPs_len, double epsN, double epsT, double mu, bool keyContactDetection, bool keyAssembleKc, bool isAxisymmetric, int nsg)
{

  int col;
  int* segmentNodesIDs = new int[nsn];
  int* segmentNodesIDm = new int[nsn];
  double* Xs = new double[nsn*nsd];
  double* Xm = new double[nsn*nsd];
  double* Us = new double[nsn*nsd];
  double* Um = new double[nsn*nsd];
  double* dXs = new double[nsn*npd];
  double* dxs = new double[nsn*npd];
  double* dXm = new double[nsn*npd];
  double* dxm = new double[nsn*npd];
  double* GAPs = new double[ngp];
  bool* activeGPs = new bool[ngp];
  double* Ns = new double[nsn*nsd];
  double* Nm1 = new double[nsn*nsd];
  double* Nm2 = new double[nsn*nsd];
  double* C_Ns = new double[nsn*nsd];
  double* C_Nm = new double[nsn*nsd];
  double* C_Ts1 = new double[nsn*nsd];
  double* C_Tm1 = new double[nsn*nsd];
  double* C_Nm1 = new double[nsn*nsd];
  double* C_Pm1 = new double[nsn*nsd];
  double* C_Ts2 = new double[nsn*nsd];
  double* C_Tm2 = new double[nsn*nsd];
  double* C_Nm2 = new double[nsn*nsd];
  double* C_Pm2 = new double[nsn*nsd];
  double* Hm = new double[nsn];
  double* dHm = new double[nsn*npd];
  double* Xi_m = new double[npd];
  double* Xi0_m = new double[npd];
  double* t_T = new double[npd];
  double* t_T0 = new double[npd];

  int len_guess = *len;
  *len = 0;

  //int n_seg = GPs_len / ngp;

  double Xp[3];
  double Xg[3];
  for (int i = 0; i < 3; ++i) {
    Xp[i] = 0.0;
    Xg[i] = 0.0;
  }

  // Fill Gc_s array by zeros:
  for (int i = 0; i < neq; ++i) {
    Gc[i] = 0.0;
  }

  for (int i = 0; i < nsg; i += ngp) {

    // Fill C_s and C_m arrays by zeros:
    for (int j = 0; j < nsn*nsd; ++j) {
      Ns[j]   = 0.0;

      C_Ns[j] = 0.0;
      C_Nm[j] = 0.0;

      Nm1[j]  = 0.0;
      C_Ts1[j] = 0.0;
      C_Tm1[j] = 0.0;
      C_Nm1[j] = 0.0;
      C_Pm1[j] = 0.0;

      if(npd == 2) {
        Nm2[j]   = 0.0;
        C_Ts2[j] = 0.0;
        C_Tm2[j] = 0.0;
        C_Nm2[j] = 0.0;
        C_Pm2[j] = 0.0;
      }
    }

    // slave element index:
    col = nsd*GPs_len;
    const int els = (int)GPs[col + i] - 1; // Matlab numbering starts with 1

    // slave segment index:
    col = (nsd + 1)*GPs_len;
    const int sgs = (int)GPs[col + i] - 1; // Matlab numbering starts with 1

    // slave segment coords Xs and displacements Us:
    for (int j = 0; j < nsn; ++j) {
      col = nes*j;
      int IENrows = ISN[col + sgs] - 1; // Matlab numbering starts with 1
      col = nen*els;
      segmentNodesIDs[j] = IEN[col + IENrows] - 1; // Matlab numbering starts with 1
      for (int k = 0; k < nsd; ++k) {
        col = k*(int)(neq / nsd);
        Xs[k*nsn + j] = X[col + segmentNodesIDs[j]];
        Us[k*nsn + j] = U[col + segmentNodesIDs[j]];
      }
    }

    for (int g = 0; g < ngp; ++g) {

      // Gausspoint gap values and activeGPs:
      activeGPs[g] = (bool) activeGPsOld[i + g];

      if (!activeGPs[g]) {
        continue;
      }

      // master element index:
      col = (nsd + npd + 4)*GPs_len;
      const int elm = (int)GPs[col + i + g] - 1; // Matlab numbering starts with 1
      // master segment index:
      col = (nsd + npd + 5)*GPs_len;
      const int sgm = (int)GPs[col + i + g] - 1; // Matlab numbering starts with 1

      // master segment coords Xm and displacements Um:
      for (int j = 0; j < nsn; ++j) {
        col = nes*j;
        int IENrowm = ISN[col + sgm] - 1; // Matlab numbering starts with 1
        col = nen*elm;
        segmentNodesIDm[j] = IEN[col + IENrowm] - 1; // Matlab numbering starts with 1
        for (int k = 0; k < nsd; ++k) {
          col = k*(int)(neq / nsd);
          Xm[k*nsn + j] = X[col + segmentNodesIDm[j]];
          Um[k*nsn + j] = U[col + segmentNodesIDm[j]];
        }
      }

      // GPs legend:              Xg     els  sgs   gap    Xi_m  isActive      elm      sgm      isStick      t_T       Xi0_m     t_N0
      //double* GPs = new double[n*(nsd + 1 +  1  +  1  +  npd  +   1     +     1    +   1     +    1    +    npd   +    npd    + 1];
      //index of begining           0    nsd nsd+1 nsd+2  nsd+3  nsd+npd+3  nsd+npd+4 nsd+npd+5 nsd+npd+6  nsd+npd+7 nsd+2*npd+7  nsd+3*npd+7 (size = nsd+3*npd+8)

      // Shape function and its derivatives of gausspoint's master segment
      double r = GPs[(nsd + 3)*GPs_len + i + g];
      double s = 0.0;

      if (npd == 2) {
        s = GPs[(nsd + 4)*GPs_len + i + g];
      }

      switch (nsn) {
        case 2:
        sfd2(Hm, dHm, r);
        break;
        case 4:
        sfd4(Hm, dHm, r, s);
        break;
        case 6:
        sfd6(Hm, dHm, r, s);
        break;
        case 8:
        sfd8(Hm, dHm, r, s);
      }

      // evaluate gausspoint coords:
      for (int sdf = 0; sdf < nsd; ++sdf) {
        Xp[sdf] = 0.0;
        Xg[sdf] = 0.0;
        for (int k = 0; k < nsn; ++k) {
          Xp[sdf] += Hm[k] * (Xm[sdf*nsn + k] + Um[sdf*nsn + k]);
          Xg[sdf] += H[k*ngp + g] * (Xs[sdf*nsn + k] + Us[sdf*nsn + k]);
        }
      }

      // if contact detection is on, the new gap is stored in the GP array
      if (keyContactDetection) {
        col = (nsd + 2)*GPs_len;
        GAPs[g] = GPs[col + i + g];
      }
      else { // else the new gap is considered as the distance between the Gauss point and its projection onto the master segment:
        // (sign is determinated later)
        /////////GAPs[g] =  sqrt( (Xp[0] - Xg[0])*(Xp[0] - Xg[0]) + (Xp[1] - Xg[1])*(Xp[1] - Xg[1]) + (Xp[2] - Xg[2])*(Xp[2] - Xg[2]) );
        // Note that for both the 2D and the 3D case the same equation is used. This is correct because Xp and Xg are initialized as 1x3 zero arrays.

        col = (nsd + 2)*GPs_len;
        GAPs[g] = GPs[col + i + g];
      }

      // Fill dXs arrays by zeros:
      for (int j = 0; j < nsn*npd; ++j) {
        dXs[j] = 0.0;
        dxs[j] = 0.0;
        dXm[j] = 0.0;
        dxm[j] = 0.0;
      }

      // Evaluate tangent vectors:
      for (int pdf = 0; pdf < npd; ++pdf) {
        for (int sdf = 0; sdf < nsd; ++sdf) {
          for (int j = 0; j < nsn; ++j) {
            col = j*npd*ngp;
            const double dh = dH[col + g*npd + pdf];
            dXs[npd*sdf + pdf] += dh*Xs[sdf*nsn + j];
            dxs[npd*sdf + pdf] += dh*(Xs[sdf*nsn + j] + Us[sdf*nsn + j]);
            dXm[npd*sdf + pdf] += dHm[j]*Xm[sdf*nsn + j];
            dxm[npd*sdf + pdf] += dHm[j]*(Xm[sdf*nsn + j] + Um[sdf*nsn + j]);
          }
        }
      }


      //       X     Y      Z
      // r   dxs[0] dxs[2]  dxs[4]
      // s   dxs[1] dxs[3]  dxs[5]

      // Matric tensor:
      double mm[4];

      mm[0] = 0.0;
      mm[1] = 0.0;
      mm[2] = 0.0;
      mm[3] = 0.0;

      for (int sdf = 0; sdf < nsd; ++sdf) {
        mm[0] += dxm[sdf*npd + 0] * dxm[sdf*npd + 0];
        if(npd == 2) {
          mm[1] += dxm[sdf*npd + 1] * dxm[sdf*npd + 0];
          mm[2] += dxm[sdf*npd + 0] * dxm[sdf*npd + 1];
          mm[3] += dxm[sdf*npd + 1] * dxm[sdf*npd + 1];
        }
      }

      // Inverse of matric tensor

      double invmm[4];
      invmm[0] = 0.0;
      invmm[1] = 0.0;
      invmm[2] = 0.0;
      invmm[3] = 0.0;

      if(npd == 1) {
        invmm[0] = 1 / mm[0];
      }
      else if(npd == 2) {
        const double invdetmm = 1 / (mm[0]*mm[3] - mm[1]*mm[2]);
        invmm[0] =  invdetmm * mm[3];
        invmm[1] = -invdetmm * mm[2];
        invmm[2] = -invdetmm * mm[1];
        invmm[3] =  invdetmm * mm[0];
      }

      // Read frictional variables:
      for (int pdf = 0; pdf < npd; ++pdf) {
        Xi_m[pdf]  = GPs[(nsd + 3 + pdf)*GPs_len + i + g];
        t_T0[pdf]  = GPs[(nsd + npd + 7 + pdf)*GPs_len + i + g];
        Xi0_m[pdf] = GPs[(nsd + 2*npd + 7 + pdf)*GPs_len + i + g];
      }

      double t_N0 = GPs[(nsd + 3*npd + 7)*GPs_len + i + g];

      // isStick is not necessary...
      //const int isStick = (int)GPs[(nsd + npd + 6)*GPs_len + i + g];

      // Evaluate trial tangent traction:
      for (int r = 0; r < npd; ++r) {
        t_T[r] = t_T0[r];
        for (int s = 0; s < npd; ++s) {
          t_T[r] -= epsT * (Xi_m[s] - Xi0_m[s]);
        }
      }

      // Evaluate norm of the trial traction vector:
      double norm_t_T = 0.0;
      for (int r = 0; r < npd; ++r) {
        for (int s = 0; s < npd; ++s) {
          norm_t_T += t_T[r]*mm[npd*s + r]*t_T[s];
        }
      }
      norm_t_T = sqrt(norm_t_T);

      // Unit vector in the direction of slip:
      double p_T[2];
      p_T[1] = 0.0;
      for (int r = 0; r < npd; ++r) {
        if(fabs(norm_t_T) > 1e-10) {
          p_T[r] = t_T[r] / norm_t_T;
        }
        else {
          p_T[r] = 0.0;
        }
      }

      // Evaluate normal vector:
      double Normal_m[3]; // normal to initial master surface
      double normal_m[3]; // normal to the current master surface
      double Normal_s[3]; // normal to initial slave surface
      double normal_s[3]; // normal to the current slave surface

      if (nsd == 2) {
        Normal_m[0] = dXm[1];
        Normal_m[1] = -dXm[0];
        Normal_m[2] = 0.0;

        normal_m[0] = dxm[1];
        normal_m[1] = -dxm[0];
        normal_m[2] = 0.0;

        Normal_s[0] = dXs[1];
        Normal_s[1] = -dXs[0];
        Normal_s[2] = 0.0;

        normal_s[0] = dxs[1];
        normal_s[1] = -dxs[0];
        normal_s[2] = 0.0;
      }
      else if (nsd == 3) {
        //       X     Y      Z
        // r   dXs[0] dXs[2]  dXs[4]
        // s   dXs[1] dXs[3]  dXs[5]
        const double dXm_dr1 = dXm[0];
        const double dXm_dr2 = dXm[npd + 0];
        const double dXm_dr3 = dXm[2 * npd + 0];
        const double dXm_ds1 = dXm[1];
        const double dXm_ds2 = dXm[npd + 1];
        const double dXm_ds3 = dXm[2 * npd + 1];
        Normal_m[0] = dXm_dr2*dXm_ds3 - dXm_dr3*dXm_ds2;
        Normal_m[1] = dXm_dr3*dXm_ds1 - dXm_dr1*dXm_ds3;
        Normal_m[2] = dXm_dr1*dXm_ds2 - dXm_dr2*dXm_ds1;

        const double dxm_dr1 = dxm[0];
        const double dxm_dr2 = dxm[npd + 0];
        const double dxm_dr3 = dxm[2 * npd + 0];
        const double dxm_ds1 = dxm[1];
        const double dxm_ds2 = dxm[npd + 1];
        const double dxm_ds3 = dxm[2 * npd + 1];
        normal_m[0] = dxm_dr2*dxm_ds3 - dxm_dr3*dxm_ds2;
        normal_m[1] = dxm_dr3*dxm_ds1 - dxm_dr1*dxm_ds3;
        normal_m[2] = dxm_dr1*dxm_ds2 - dxm_dr2*dxm_ds1;


        const double dXs_dr1 = dXs[0];
        const double dXs_dr2 = dXs[npd + 0];
        const double dXs_dr3 = dXs[2 * npd + 0];
        const double dXs_ds1 = dXs[1];
        const double dXs_ds2 = dXs[npd + 1];
        const double dXs_ds3 = dXs[2 * npd + 1];
        Normal_s[0] = dXs_dr2*dXs_ds3 - dXs_dr3*dXs_ds2;
        Normal_s[1] = dXs_dr3*dXs_ds1 - dXs_dr1*dXs_ds3;
        Normal_s[2] = dXs_dr1*dXs_ds2 - dXs_dr2*dXs_ds1;

        const double dxs_dr1 = dxs[0];
        const double dxs_dr2 = dxs[npd + 0];
        const double dxs_dr3 = dxs[2 * npd + 0];
        const double dxs_ds1 = dxs[1];
        const double dxs_ds2 = dxs[npd + 1];
        const double dxs_ds3 = dxs[2 * npd + 1];
        normal_s[0] = dxs_dr2*dxs_ds3 - dxs_dr3*dxs_ds2;
        normal_s[1] = dxs_dr3*dxs_ds1 - dxs_dr1*dxs_ds3;
        normal_s[2] = dxs_dr1*dxs_ds2 - dxs_dr2*dxs_ds1;
      }

      double jacobian_s = sqrt(Normal_s[0] * Normal_s[0] + Normal_s[1] * Normal_s[1] + Normal_s[2] * Normal_s[2]);
      if(isAxisymmetric) {
        jacobian_s *= 2 * M_PI * Xg[0];
      }

      const double normal_m_length = sqrt(normal_m[0] * normal_m[0] + normal_m[1] * normal_m[1] + normal_m[2] * normal_m[2]);
      normal_m[0] /= normal_m_length;
      normal_m[1] /= normal_m_length;
      normal_m[2] /= normal_m_length;

      const double normal_s_length = sqrt(normal_s[0] * normal_s[0] + normal_s[1] * normal_s[1] + normal_s[2] * normal_s[2]);
      normal_s[0] /= normal_s_length;
      normal_s[1] /= normal_s_length;
      normal_s[2] /= normal_s_length;
/*
      if (!keyContactDetection) {
        const double signGAPs = (Xp[0] - Xg[0])*normal_m[0] + (Xp[1] - Xg[1])*normal_m[1] + (Xp[2] - Xg[2])*normal_m[2];
        if (signGAPs < 0.0) { // Possitive signGAPs means open gap which is defined as negative GAP.
          GAPs[g] = -GAPs[g];
        }
        GPs[(nsd + 2)*GPs_len + i + g] = GAPs[g];
      }
      else { // Change active state only when contact detection is enabled

        if (GAPs[g] < 0.0) {
          GPs[(nsd + npd + 3)*GPs_len + i + g] = 0; // negative GAP means open gap which means inActive GP
          continue;
        } else {
          GPs[(nsd + npd + 3)*GPs_len + i + g] = 1; // possitive GAP means penetration which means Active GP
        }
      }
*/

  //if (els > 100 && els < 1800) epsN = 1e3;

      double t_N_new = -epsN*GAPs[g];

      double t_N = t_N0 + t_N_new; // normal contact traction component is non-positive, i.e. compression
      //std::cout << "t_N0 = " << t_N0 << ", t_N_new = " << t_N_new << std::endl;

      if(t_N > 0.0) {
        t_N = 0.0;
        //std::cout << "g_N = " << GAPs[g] << ", t_N_g = " << t_N << std::endl;
        GPs[(nsd + 3*npd + 7)*GPs_len + i + g] = t_N;
        continue;
      }
      GPs[(nsd + 3*npd + 7)*GPs_len + i + g] = t_N;



      bool isStick = false;

      // Check slip function:
      if(norm_t_T + mu*t_N  <= 1e-10) {
        //printf("stick ");
        isStick = true;
        for (int pdf = 0; pdf < npd; ++pdf) {
          GPs[(nsd + npd + 7 + pdf)*GPs_len + i + g] = t_T[pdf];
        }
      }
      else {
        isStick = false;
        printf("slip ");
        for (int pdf = 0; pdf < npd; ++pdf) {
          if(norm_t_T > 1e-10) {
            t_T[pdf] = -mu*t_N * p_T[pdf];
          }
          else {
            t_T[pdf] = 0.0;
          }
          GPs[(nsd + npd + 7 + pdf)*GPs_len + i + g] = t_T[pdf];
        }
      }

      double tau[3];
      tau[0] = dxm[0];
      tau[1] = dxm[1];
      tau[2] = 0.0;

      // evaluate shape functions and contact residual vectors:
      for (int j = 0; j < nsn; ++j) {
        const double hs = H[j*ngp + g];
        const double hm = Hm[j];

        for (int sdf = 0; sdf < nsd; ++sdf) {

          Ns[j*nsd + sdf]   += hs;
          C_Ns[j*nsd + sdf] += hs*normal_m[sdf];
          C_Nm[j*nsd + sdf] += hm*normal_m[sdf];

          Nm1[j*nsd + sdf]   += dHm[j];
          C_Ts1[j*nsd + sdf] += hs*tau[sdf];//dXm[sdf*npd];
          C_Tm1[j*nsd + sdf] += hm*tau[sdf];//dXm[sdf*npd];
          C_Nm1[j*nsd + sdf] += dHm[j]*normal_m[sdf];
          C_Pm1[j*nsd + sdf] += dHm[j]*p_T[0];

          if(npd == 2) {
            Nm2[j*nsd + sdf]   += dHm[nsn + j];
            C_Ts2[j*nsd + sdf] += hs*dxm[sdf*npd+1];
            C_Tm2[j*nsd + sdf] += hm*dxm[sdf*npd+1];
            C_Nm2[j*nsd + sdf] += dHm[nsn + j]*normal_m[sdf];
            C_Pm2[j*nsd + sdf] += dHm[nsn + j]*p_T[1];
          }

          // The negative master normal is used as the slave normal
          //sstd::cout << t_N << ", " << hs << ", " << normal_m[sdf] << " , " << gw[g] << ", " << jacobian_s << std::endl;
          Gc[segmentNodesIDs[j] * nsd + sdf]   -= t_N * hs * (-normal_m[sdf]) * gw[g] * jacobian_s;
          Gc_loc[ (i+g)*(j*nsd + sdf) + i/ngp] -= t_N * hs * (-normal_m[sdf]) * gw[g] * jacobian_s;

          //////////// For MASTER-SLAVE t_N * hm term is needed (loop over GPs tabel goes only over SLAVE GPs)
          if (GPs_len != nsg) { // This inequality indicates master-slave algorithm
            Gc[segmentNodesIDm[j] * nsd + sdf]    -= t_N * hm * (normal_m[sdf]) * gw[g] * jacobian_s;
          }

          // MUSI SE UPRAVIT: Gc_loc[ (i+g)*(j*nsd + sdf) + i/ngp]  = t_N * hm * (-normal_m[sdf]) * gw[g] * jacobian_s;

          /*
          for (int pdf = 0; pdf < npd; ++pdf) {
          Gc[segmentNodesIDs[j] * nsd + sdf]   -= t_T[pdf]*hs*tau[sdf] * gw[g] * jacobian_s;
          Gc_loc[ (i+g)*(j*nsd + sdf) + i/ngp] -= t_T[pdf]*hs*tau[sdf] * gw[g] * jacobian_s;
        }
        */

      }
    }

    if(keyAssembleKc) {
      for (int j = 0; j < nsn*nsd; ++j) { // loop over cols
        for (int k = 0; k < nsn*nsd; ++k) { // loop over rows

          // Kc elementu je blokova matice o strukture:
          // Kc_e = [C_Nm*C_Nm'  C_Nm*C_Ns'
          //         C_Ns*C_Nm'  C_Ns*C_Ns'];
          // dimeze: [(nsn*nsd)*(nsn*nsd)  (nsn*nsd)*(nsn*nsd)
          //          (nsn*nsd)*(nsn*nsd)  (nsn*nsd)*(nsn*nsd)];

          Kc[(i+g)*2*nsn*nsd*k           + (i+g)*(nsn*nsd+j) + i/ngp] = C_Ns[j] * C_Nm[k] * gw[g] * jacobian_s;
          Kc[(i+g)*2*nsn*nsd*(nsn*nsd+k) + (i+g)*(nsn*nsd+j) + i/ngp] = C_Ns[j] * C_Ns[k] * gw[g] * jacobian_s;

          const int jdof = j%nsd;
          const int jnode = (j - jdof) / nsd; // row node

          const int kdof = k%nsd;
          const int knode = (k - kdof) / nsd; // col node


          /////////////////// Normal contact /////////////////////////////

          if(fabs(C_Ns[k] * C_Ns[j]) > 1e-50) {
            cols[*len] = segmentNodesIDs[jnode] * nsd + jdof + 1;
            rows[*len] = segmentNodesIDs[knode] * nsd + kdof + 1;
            vals[*len] = epsN * (C_Ns[k] * C_Ns[j]) * gw[g] * jacobian_s;
            (*len)++;
            if (*len >= len_guess) printf("Error, len is too small: len = %i.\n", len_guess);
          }


          if(fabs(C_Ns[k] * C_Nm[j]) > 1e-50) {
            cols[*len] = segmentNodesIDm[jnode] * nsd + jdof + 1;
            rows[*len] = segmentNodesIDs[knode] * nsd + kdof + 1;
            vals[*len] = epsN * (-C_Ns[k] * C_Nm[j]) * gw[g] * jacobian_s;
            (*len)++;
            if (*len >= len_guess) printf("Error, len is too small: len = %i.\n", len_guess);
          }


        if(fabs(C_Ts1[k] * C_Nm1[j]) > 1e-50) {
          cols[*len] = segmentNodesIDm[jnode] * nsd + jdof + 1;
          rows[*len] = segmentNodesIDs[knode] * nsd + kdof + 1;
          vals[*len] = t_N * invmm[0] * (C_Ts1[k] * C_Nm1[j]) * gw[g] * jacobian_s;
          (*len)++;
          if (*len >= len_guess) printf("Error, len is too small: len = %i.\n", len_guess);
        }


        if (GPs_len != nsg) { // This inequality indicates master-slave algorithm
          //////////// For MASTER-SLAVE C_Nm*C_Nm term is needed (loop over GPs tabel goes only over SLAVE GPs)
          if(fabs(C_Nm[k] * C_Nm[j]) > 1e-50) {
            cols[*len] = segmentNodesIDm[jnode] * nsd + jdof + 1;
            rows[*len] = segmentNodesIDm[knode] * nsd + kdof + 1;
            vals[*len] = epsN * (C_Nm[k] * C_Nm[j]) * gw[g] * jacobian_s;
            (*len)++;
            if (*len >= len_guess) printf("Error, len is too small: len = %i.\n", len_guess);
          }

          if(fabs(C_Nm[k] * C_Ns[j]) > 1e-50) {
            cols[*len] = segmentNodesIDs[jnode] * nsd + jdof + 1;
            rows[*len] = segmentNodesIDm[knode] * nsd + kdof + 1;
            vals[*len] = epsN * (-C_Nm[k] * C_Ns[j]) * gw[g] * jacobian_s;
            (*len)++;
            if (*len >= len_guess) printf("Error, len is too small: len = %i.\n", len_guess);
          }
        }

        if(isStick) { ////////////////// stick ///////////////////
          /*
          cols[*len] = segmentNodesIDs[jnode] * nsd + jdof + 1;
          rows[*len] = segmentNodesIDs[knode] * nsd + kdof + 1;
          vals[*len] = +epsT * invmm[0] *(C_Ts1[k] * C_Ts1[j]) * gw[g] * jacobian_s;
          (*len)++;
          if (*len >= len_guess) printf("Error, len is too small: len = %i.\n", len_guess);

          cols[*len] = segmentNodesIDm[jnode] * nsd + jdof + 1;
          rows[*len] = segmentNodesIDs[knode] * nsd + kdof + 1;
          vals[*len] = +epsT * invmm[0] *(-C_Ts1[k] * C_Tm1[j]) * gw[g] * jacobian_s;
          (*len)++;
          if (*len >= len_guess) printf("Error, len is too small: len = %i.\n", len_guess);

          cols[*len] = segmentNodesIDm[jnode] * nsd + jdof + 1;
          rows[*len] = segmentNodesIDs[knode] * nsd + kdof + 1;
          vals[*len] = +epsT * invmm[0] *(-GAPs[g] * C_Ts1[k] * C_Nm1[j]) * gw[g] * jacobian_s;
          (*len)++;
          if (*len >= len_guess) printf("Error, len is too small: len = %i.\n", len_guess);

          cols[*len] = segmentNodesIDm[jnode] * nsd + jdof + 1;
          rows[*len] = segmentNodesIDs[knode] * nsd + kdof + 1;
          vals[*len] = -t_T[0] * (Ns[k] * Nm1[j]) * gw[g] * jacobian_s;
          (*len)++;
          if (*len >= len_guess) printf("Error, len is too small: len = %i.\n", len_guess);
          */
        }
        else { ////////////////////// slip ////////////////////////
          /*
          cols[*len] = segmentNodesIDs[jnode] * nsd + jdof + 1;
          rows[*len] = segmentNodesIDs[knode] * nsd + kdof + 1;
          vals[*len] = +mu * epsN * p_T[0] * (C_Ts1[k] * C_Ns[j]) * gw[g] * jacobian_s;
          (*len)++;
          if (*len >= len_guess) printf("Error, len is too small: len = %i.\n", len_guess);

          cols[*len] = segmentNodesIDm[jnode] * nsd + jdof + 1;
          rows[*len] = segmentNodesIDs[knode] * nsd + kdof + 1;
          vals[*len] = +mu * epsN * p_T[0] * (-C_Ts1[k] * C_Nm[j]) * gw[g] * jacobian_s;
          (*len)++;
          if (*len >= len_guess) printf("Error, len is too small: len = %i.\n", len_guess);

          cols[*len] = segmentNodesIDm[jnode] * nsd + jdof + 1;
          rows[*len] = segmentNodesIDs[knode] * nsd + kdof + 1;
          vals[*len] = +mu * t_N * p_T[0] * p_T[0] * (C_Ts1[k] * C_Pm1[j]) * gw[g] * jacobian_s;
          (*len)++;
          if (*len >= len_guess) printf("Error, len is too small: len = %i.\n", len_guess);

          cols[*len] = segmentNodesIDm[jnode] * nsd + jdof + 1;
          rows[*len] = segmentNodesIDs[knode] * nsd + kdof + 1;
          vals[*len] = -t_T[0] * (Ns[k] * Nm1[j]) * gw[g] * jacobian_s;
          (*len)++;
          if (*len >= len_guess) printf("Error, len is too small: len = %i.\n", len_guess);
          */
        }
      }
    }
  }

  // Fill C_m array by zeros:
  for (int j = 0; j < nsn*nsd; ++j) {
    Ns[j] = 0.0;
    C_Ns[j] = 0.0;
    C_Nm[j] = 0.0;

    Nm1[j] = 0.0;
    C_Ts1[j] = 0.0;
    C_Tm1[j] = 0.0;
    C_Nm1[j] = 0.0;
    C_Pm1[j] = 0.0;

    if(npd == 2) {
      Nm2[j] = 0.0;
      C_Ts2[j] = 0.0;
      C_Tm2[j] = 0.0;
      C_Nm2[j] = 0.0;
      C_Pm2[j] = 0.0;
    }
  }

} // loop over gausspoints
} // loop over GPs rows

delete[] segmentNodesIDs;
delete[] segmentNodesIDm;
delete[] Xs;
delete[] Xm;
delete[] Us;
delete[] Um;
delete[] dXs;
delete[] dxs;
delete[] GAPs;
delete[] activeGPs;
delete[] Ns;
delete[] C_Ns;
delete[] C_Nm;
delete[] Nm1;
delete[] C_Ts1;
delete[] C_Tm1;
delete[] C_Nm1;
delete[] C_Pm1;

delete[] C_Ts2;
delete[] C_Tm2;
delete[] Nm2;
delete[] C_Nm2;
delete[] C_Pm2;
delete[] Hm;
delete[] dHm;
delete[] Xi_m;
delete[] Xi0_m;
delete[] t_T;
delete[] t_T0;
}

void getLongestEdgeAndGPs(double* longestEdge, double* GPs, int n, int nsd, int npd, int ngp, int neq, int nsn, int nes, int nen, int* elementID, int* segmentID, int* ISN, int* IEN, double* H, double* X) {
  // GPs legend:              Xg     els  sgs   gap    Xi_m  isActive      elm      sgm      isStick      t_T       Xi0_m     t_N0
  //double* GPs = new double[n*(nsd + 1 +  1  +  1  +  npd  +   1     +     1    +   1     +    1    +    npd   +    npd    +  1];
  //index of begining           0    nsd nsd+1 nsd+2  nsd+3  nsd+npd+3  nsd+npd+4 nsd+npd+5 nsd+npd+6  nsd+npd+7 nsd+2*npd+7   (size = nsd+3*npd+8)

  int* segmentNodesID = new int[nsn];
  double* Xs = new double[nsn*nsd];
  double* Xg = new double[ngp*nsd];
  int g = 0;
  *longestEdge = 0.0;

  for (int e = 0; e < n; ++e) {
    int el = elementID[e] - 1;
    int sg = segmentID[e] - 1;

    // segment coords Xs:
    for (int i = 0; i < nsn; ++i) {
      const int IENrow = ISN[nes*i + sg] - 1; // Matlab numbering starts with 1
      segmentNodesID[i] = IEN[nen*el + IENrow] - 1; // Matlab numbering starts with 1
      for (int j = 0; j < nsd; ++j) {
        Xs[j*nsn + i] = X[j*(int)(neq / nsd) + segmentNodesID[i]];
      }
    }

    // evaluate gausspoint coords:
    for (int i = 0; i < ngp; ++i) {
      for (int sdf = 0; sdf < nsd; ++sdf) {
        Xg[i*nsd + sdf] = 0.0;
        for (int j = 0; j < nsn; ++j) {
          Xg[i*nsd + sdf] += H[j*ngp + i] * Xs[sdf*nsn + j];
        }

        GPs[sdf*n*ngp + g] = Xg[i*nsd + sdf]; // slave gausspoint coords
        //GPs[(nsd + 3 + sdf)*n*ngp + g] = 0.0; // init master parametric coords Xi_m
      }

      GPs[(nsd + 0)*n*ngp + g] = el + 1;      // slave element
      GPs[(nsd + 1)*n*ngp + g] = sg + 1;      // slave segment
      GPs[(nsd + 2)*n*ngp + g] = -FLT_MAX;    // init gap

      for (int pdf = 0; pdf < npd; ++pdf) {
        GPs[(nsd + 3 + pdf)*n*ngp + g] = 0.0; // Xi_m
      }

      GPs[(nsd + npd + 3)*n*ngp + g] = 0;       // init is NO active
      GPs[(nsd + npd + 4)*n*ngp + g] = 0;       // master element
      GPs[(nsd + npd + 5)*n*ngp + g] = 0;       // master segment
      GPs[(nsd + npd + 6)*n*ngp + g] = 0;       // is stick

      for (int pdf = 0; pdf < nsd-1; ++pdf) {
        GPs[(nsd + npd + 7 + pdf)*n*ngp + g] = 0.0; // tangent traction components
      }
      for (int pdf = 0; pdf < nsd-1; ++pdf) {
        GPs[(nsd + 2*npd + 7 + pdf)*n*ngp + g] = 0.0; // Xi0_m
      }
      GPs[(nsd + 3*npd + 7)*n*ngp + g] = 0.0; // t_N0
      g++;
    }

    for (int i = 0; i < nsn; ++i) {
      for (int j = i+1; j < nsn; ++j) {
        double lengthOfEdge = 0.0;
        for (int sdf = 0; sdf < nsd; ++sdf) {
          lengthOfEdge += pow(Xs[sdf*nsn + i] - Xs[sdf*nsn + j ], 2);
        }
        *longestEdge = std::max(*longestEdge, sqrt(lengthOfEdge) );
      }
    }

  } // loop over elements

  delete[] segmentNodesID;
  delete[] Xs;
  delete[] Xg;

}

void getAABB(double* AABBmin, double* AABBmax, int nsd, int nnod, double* X, double longestEdge, int* IEN, int* ISN, int* elementID, int* segmentID, int n, int nsn, int nes, int nen, int neq) {

  int* segmentNodesID = new int[nsn];

  for (int sdf = 0; sdf < nsd; ++sdf) {
    AABBmin[sdf] = FLT_MAX;
    AABBmax[sdf] = -FLT_MAX;

    for (int e = 0; e < n; ++e) {
      int el = elementID[e] - 1;
      int sg = segmentID[e] - 1;

      // segment coords Xs:
      for (int i = 0; i < nsn; ++i) {
        const int IENrow = ISN[nes*i + sg] - 1; // Matlab numbering starts with 1
        segmentNodesID[i] = IEN[nen*el + IENrow] - 1; // Matlab numbering starts with 1
        //	for (int sdf = 0; sdf < nsd; ++sdf) {
        const double x = X[sdf*(int)(neq / nsd) + segmentNodesID[i]];
        AABBmin[sdf] = std::min(AABBmin[sdf], x);
        AABBmax[sdf] = std::max(AABBmax[sdf], x);
        //	}
      }
    }

    //for (int sdf = 0; sdf < nsd; ++sdf) {
    //if ((AABBmax[sdf] - AABBmin[sdf]) < longestEdge) {
    //  AABBmax[sdf] += 0.5*longestEdge;
    //  AABBmin[sdf] -= 0.5*longestEdge;
    //}
    //}
  }
  delete[] segmentNodesID;
}

/*! Calculate contact residual term (gradient) and contact tangent term (Hessian)

\param GPs - 2d array (GPs_len x ??? cols)
\param ISN - 2d array (nsn*)
\param IEN -
\param N -
\param AABBmin -
\param AABBmax -
\param head -
\param next -
\param X - 2d array of contact nodal coordinates
\param elementID -
\param segmentID -
\param n - number of contact segments
\param nsn - Number of Segment Nodes
\param nsd - Number of Space Dimensions
\param npd - Number of Parametric Dimensions
\param ngp - Number of Gauss Points
\param nen - Number of Element Nodes
\param nes - Number of Element Segments
\param neq - Number of EQuations
\param longestEdge - length of the longest edge of all contact segments

\return GPs - 1d array
*/
void evaluateContactConstraints(double* GPs, int* ISN, int* IEN, int* N, double* AABBmin, double* AABBmax, int* head, int* next, double* X, int* elementID, int* segmentID, int n, int nsn, int nsd, int npd, int ngp, int nen, int nes, int neq, double longestEdge) {

  // GPs legend:              Xg     els  sgs   gap    Xi_m  isActive      elm      sgm      isStick      t_T       Xi0_m
  //double* GPs = new double[n*(nsd + 1 +  1  +  1  +  npd  +   1     +     1    +   1     +    1    +    npd   +    npd    ];
  //index of begining           0    nsd nsd+1 nsd+2  nsd+3  nsd+npd+3  nsd+npd+4 nsd+npd+5 nsd+npd+6  nsd+npd+7 nsd+2*npd+7  (size = nsd+3*npd+7)


  int* segmentNodesID = new int[nsn];
  double* Xm = new double[nsn*3];
  double* Xmin = new double[nsd];
  double* Xmax = new double[nsd];
  double* Hm = new double[nsn];
  double* dHm = new double[nsn*npd];

  double Xt[9];
  double Xc[3];

  for(int i = 0; i < 3; ++i) Xc[i] = 0.0;
  for(int i = 0; i < 9; ++i) Xt[i] = 0.0;
  for(int i = 0; i < nsn*3; ++i) Xm[i] = 0.0;


  // Number of TRiangles:
  int ntr = 1;
  if(nsn == 8) {
    // If the segment element is a quad then it is subdivided to 4 triangles (with a common vertex Xc in the centre of mass):
    ntr = 4;
  }

  // Initialize the gap by MINUS float max value (because negative is OPEN gap:
  int numOfRows = n*ngp;
  int colBegin = (nsd + 2) * numOfRows;
  for (int row = 0; row < numOfRows; ++row) {
    GPs[colBegin + row] = -FLT_MAX;
  }

  // Loop over contact segments:
  for (int e = 0; e < n; ++e) {
    int el = elementID[e] - 1;
    int sg = segmentID[e] - 1;

    // segment coords Xm:
    for (int k = 0; k < nsd; ++k) {

      Xmin[k] = FLT_MAX;
      Xmax[k] = -FLT_MAX;
      Xc[k] = 0.0;

      for (int j = 0; j < nsn; ++j) {
        const int IENrow = ISN[nes*j + sg] - 1; // Matlab numbering starts with 1
        segmentNodesID[j] = IEN[nen*el + IENrow] - 1; // Matlab numbering starts with 1
        Xm[k*nsn + j] = X[k*(int)(neq / nsd) + segmentNodesID[j]];
        Xmin[k] = std::min(Xmin[k], Xm[k*nsn + j]);
        Xmax[k] = std::max(Xmax[k], Xm[k*nsn + j]);
        Xc[k] += Xm[k*nsn + j];
      }
      Xmin[k] -= 0.5*longestEdge;
      Xmax[k] += 0.5*longestEdge;
      Xc[k] /= nsn;
    }

    // Loop over segment triangles:
    for (int it = 0; it < ntr; ++it) {

      if(nsd == 3) {
        // triangle coords Xt:
        if(ntr == 1) {
          Xt[0] = Xm[0];
          Xt[1] = Xm[1];
          Xt[2] = Xm[2];

          Xt[3] = Xm[nsn];
          Xt[4] = Xm[nsn+1];
          Xt[5] = Xm[nsn+2];

          Xt[6] = Xm[2*nsn];
          Xt[7] = Xm[2*nsn+1];
          Xt[8] = Xm[2*nsn+2];
        }
        else if(ntr == 4) {
          Xt[0] = Xm[it];
          Xt[1] = Xm[it+1];
          Xt[2] = Xc[0];

          Xt[3] = Xm[nsn+it];
          Xt[4] = Xm[nsn+it+1];
          Xt[5] = Xc[1];

          Xt[6] = Xm[2*nsn+it];
          Xt[7] = Xm[2*nsn+it+1];
          Xt[8] = Xc[2];
        }

        // Min and Max of the triangle coords:
        for (int k = 0; k < nsd; ++k) {
          Xmin[k] = FLT_MAX;
          Xmax[k] = -FLT_MAX;
          for (int j = 0; j < 3; ++j) {
            Xmin[k] = std::min(Xmin[k], Xt[k*3 + j]);
            Xmax[k] = std::max(Xmax[k], Xt[k*3 + j]);
          }
          Xmin[k] -= 0.5*longestEdge;
          Xmax[k] += 0.5*longestEdge;
        }
      }

      int Imin[3];
      int Imax[3];
      double normal[3];
      double t1[3];
      double t2[3];
      double t3[3];
      double Xg[3];
      double Xp[3];

      Imin[0] = (int)(N[0] * (Xmin[0] - AABBmin[0]) / (AABBmax[0] - AABBmin[0]));
      Imin[1] = (int)(N[1] * (Xmin[1] - AABBmin[1]) / (AABBmax[1] - AABBmin[1]));
      Imax[0] = (int)(N[0] * (Xmax[0] - AABBmin[0]) / (AABBmax[0] - AABBmin[0]));
      Imax[1] = (int)(N[1] * (Xmax[1] - AABBmin[1]) / (AABBmax[1] - AABBmin[1]));

      if (nsd == 2) {

        Imin[2] = 0;
        Imax[2] = 0;

        t1[0] = Xm[1] - Xm[0];
        t1[1] = Xm[3] - Xm[2];
        t1[2] = 0.0;

        normal[0] = t1[1];
        normal[1] = -t1[0];
        normal[2] = 0.0;
      }
      else if (nsd == 3) {

        Imin[2] = (int)(N[2] * (Xmin[2] - AABBmin[2]) / (AABBmax[2] - AABBmin[2]));
        Imax[2] = (int)(N[2] * (Xmax[2] - AABBmin[2]) / (AABBmax[2] - AABBmin[2]));

        // Tangent vectors parallel with element edges 1 and 2:
        // Component: X     Y      Z
        // Vertex 1:  Xt[0] Xt[3]  Xt[6]
        // Vertex 2:  Xt[1] Xt[4]  Xt[7]
        // Vertex 3:  Xt[2] Xt[5]  Xt[8]

        t1[0] = Xt[1] - Xt[0];
        t1[1] = Xt[4] - Xt[3];
        t1[2] = Xt[7] - Xt[6];

        t2[0] = Xt[2] - Xt[1];
        t2[1] = Xt[5] - Xt[4];
        t2[2] = Xt[8] - Xt[7];

        t3[0] = Xt[0] - Xt[2];
        t3[1] = Xt[3] - Xt[5];
        t3[2] = Xt[6] - Xt[8];

        // Normal vector:
        normal[0] = t1[1] * t2[2] - t1[2] * t2[1];
        normal[1] = t1[2] * t2[0] - t1[0] * t2[2];
        normal[2] = t1[0] * t2[1] - t1[1] * t2[0];
      }

      const double normalLength = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
      normal[0] /= normalLength;
      normal[1] /= normalLength;
      normal[2] /= normalLength;

      for (int sdf = 0; sdf < nsd; ++sdf) {
        if (Imin[sdf] < 0) {
          Imin[sdf] = 0;
        }
        if (Imax[sdf] < 0) {
          Imax[sdf] = 0;
        }
        if (Imin[sdf] >= N[sdf]) {
          Imin[sdf] = N[sdf] - 1;
        }
        if (Imax[sdf] >= N[sdf]) {
          Imax[sdf] = N[sdf] - 1;
        }
      }

      for (int i2 = Imin[2]; i2 <= Imax[2]; ++i2) {
        for (int i1 = Imin[1]; i1 <= Imax[1]; ++i1) {
          for (int i0 = Imin[0]; i0 <= Imax[0]; ++i0) {
            const int Ic = i2*N[0] * N[1] + i1*N[0] + i0;
            int v = head[Ic];

            // Contact searching algorithm based on linked lists ( DOI: 10.1007/BF02487690, DOI: 10.1007/s00466-014-1058-5):
            while (v != -1) {
              // v sequentially refers to the row in the GPs table of all Gauss points that lie in the "bucket" with the index Ic.

              // Read from table GPs the index of element and the local contact segment index:
              int els = GPs[nsd*n*ngp + v] -1;            // slave element
              int sgs = GPs[(nsd + 1)*n*ngp + v] -1;      // slave segment

              // Jump if Gausspoint segment is equal to master segment
              if (el == els && sg == sgs) {
                v = next[v];
                continue;
              }

              double d;

              // Inside-outside algorithm ( DOI: 10.1002/(SICI)1097-0207(19971015)40:19<3665::AID-NME234>3.0.CO;2-K ):
              bool isInside = false;
              if (nsd == 2) {
                double r[2];
                d = 0.0;
                double t1_norm = 0.0;
                for (int i = 0; i < nsd; ++i) {
                  Xg[i] = GPs[i*n*ngp + v];
                  r[i] = Xg[i] - Xm[i*nsn + 0];
                  d += r[i] * t1[i];
                  t1_norm += t1[i] * t1[i];
                }
                t1_norm = sqrt(t1_norm);
                d = d / t1_norm;

                // Check if inside edge_1:
                if (d > 0.0 && d < t1_norm) {
                  isInside = true;
                  double sign = 0.0;
                  double d_aux = d;
                  d = 0.0;
                  for (int i = 0; i < nsd; ++i) {
                    Xp[i] = Xm[i*nsn + 0] + d_aux * t1[i] / t1_norm;
                    sign -= (Xg[i] - Xp[i])*normal[i]; // negative sign for the OPEN gap!
                    d += pow(Xg[i] - Xp[i], 2);
                  }
                  d = sqrt(d);
                  if (sign < 0) { // OPEN gap
                    d *= -1; // because d was distance (non negative number)
                  }
                }
              }
              else if (nsd == 3) {
                double r[9];
                double Q1[3];
                double Q2[3];
                double Q3[3];
                d = 0.0;
                for (int i = 0; i < nsd; ++i) {
                  Xg[i] = GPs[i*n*ngp + v];
                  r[i * 3 + 0] = Xg[i] - Xt[i*3 + 0];
                  r[i * 3 + 1] = Xg[i] - Xt[i*3 + 1];
                  r[i * 3 + 2] = Xg[i] - Xt[i*3 + 2];
                }

                // component:  X    Y    Z
                // r1:       r[0] r[3] r[6]
                // r2:       r[1] r[4] r[7]
                // r3:       r[2] r[5] r[8]
                Q1[0] = r[3] * t1[2] - r[6] * t1[1];
                Q1[1] = r[6] * t1[0] - r[0] * t1[2];
                Q1[2] = r[0] * t1[1] - r[3] * t1[0];

                Q2[0] = r[4] * t2[2] - r[7] * t2[1];
                Q2[1] = r[7] * t2[0] - r[1] * t2[2];
                Q2[2] = r[1] * t2[1] - r[4] * t2[0];

                Q3[0] = r[5] * t3[2] - r[8] * t3[1];
                Q3[1] = r[8] * t3[0] - r[2] * t3[2];
                Q3[2] = r[2] * t3[1] - r[5] * t3[0];

                const double Q1n = Q1[0] * normal[0] + Q1[1] * normal[1] + Q1[2] * normal[2];
                const double Q2n = Q2[0] * normal[0] + Q2[1] * normal[1] + Q2[2] * normal[2];
                const double Q3n = Q3[0] * normal[0] + Q3[1] * normal[1] + Q3[2] * normal[2];

                if (Q1n*Q2n > 0) {
                  if (Q1n*Q3n > 0) {
                    isInside = true;
                    d = r[0] * normal[0] + r[3] * normal[1] + r[6] * normal[2];
                    for (int i = 0; i < nsd; ++i) {
                      Xp[i] = Xg[i] - d*normal[i];
                    }
                  }
                }
              } // else if (nsd = 3)

              if (isInside) {

                // Perform a more accurate search if the current gap
                // is smaller than the previously detected but not
                // smaller than the width of the contact zone:

                if (d > GPs[(nsd + 2)*n*ngp + v] && d < 20.0) {

                  // Initial guess of the parametric coordinates on the triangle:
                  double r_len, r;
                  double s_len, s;
                  switch (nsn) { // Number of Segment Nodes
                    case 2:
                    // Tangent vectors parallel with element edges 1 and 2:
                    // Component: X     Y      Z
                    // Node 1:  Xm[0] Xm[2]  Xm[4]
                    // Node 2:  Xm[1] Xm[3]  Xm[5]

                    r_len = pow(Xm[1] - Xm[0], 2.0) +
                    pow(Xm[3] - Xm[2], 2.0) +
                    pow(Xm[5] - Xm[4], 2.0);

                    r = ((Xp[0] - Xm[0])  * (Xm[1] - Xm[0]) +
                    (Xp[1] - Xm[2])  * (Xm[3] - Xm[2]) +
                    (Xp[2] - Xm[4])  * (Xm[5] - Xm[4])) / r_len;
                    r = 2*r-1;
                    break;
                    case 6:
                    r_len = pow(Xm[1] - Xm[0], 2.0) +
                    pow(Xm[7] - Xm[6], 2.0) +
                    pow(Xm[13] - Xm[12], 2.0);

                    s_len = pow(Xm[2] - Xm[0], 2.0) +
                    pow(Xm[8] - Xm[6], 2.0) +
                    pow(Xm[14] - Xm[12], 2.0);

                    r = ((Xp[0] - Xm[0])  * (Xm[1] - Xm[0]) +
                    (Xp[1] - Xm[6])  * (Xm[7] - Xm[6]) +
                    (Xp[2] - Xm[12]) * (Xm[13] - Xm[12])) / r_len;

                    s = ((Xp[0] - Xm[0])  * (Xm[2] - Xm[0]) +
                    (Xp[1] - Xm[6])  * (Xm[8] - Xm[6]) +
                    (Xp[2] - Xm[12]) * (Xm[14] - Xm[12])) / s_len;
                    break;
                    case 8:
                    r_len = pow(Xm[1]  - Xm[0],  2.0) +
                    pow(Xm[9]  - Xm[8],  2.0) +
                    pow(Xm[17] - Xm[16], 2.0);

                    s_len = pow(Xm[3]  - Xm[0],  2.0) +
                    pow(Xm[11] - Xm[8],  2.0) +
                    pow(Xm[19] - Xm[16], 2.0);

                    r = ((Xp[0] - Xm[0])  * (Xm[1] - Xm[0]) +
                    (Xp[1] - Xm[8])  * (Xm[9] - Xm[8]) +
                    (Xp[2] - Xm[16]) * (Xm[17] - Xm[16])) / r_len;

                    r = 2*r-1;

                    s = ((Xp[0] - Xm[0])  * (Xm[3]  - Xm[0]) +
                    (Xp[1] - Xm[8])  * (Xm[11] - Xm[8]) +
                    (Xp[2] - Xm[16]) * (Xm[19] - Xm[16])) / s_len;

                    s = 2*s-1;
                  }


                  // Local contact search by Least-square projection method:
                  double dr_norm;
                  int niter = 0;
                  int max_niter = 1000;
                  do {
                    switch (nsn) {
                      case 2:
                      sfd2(Hm, dHm, r);
                      break;
                      case 4:
                      sfd4(Hm, dHm, r, s);
                      break;
                      case 6:
                      sfd6(Hm, dHm, r, s);
                      break;
                      case 8:
                      sfd8(Hm, dHm, r, s);
                    }

                    double b1, b2, A11, A22, A12;
                    A11 = 0.0;
                    A22 = 0.0;
                    A12 = 0.0;
                    b1 = 0.0;
                    b2 = 0.0;
                    d = 0.0;

                    double Xp[3];
                    double dx_dr[3];
                    double dx_ds[3];
                    double normal[3];

                    for (int sdf = 0; sdf < nsd; ++sdf) {
                      Xp[sdf] = 0.0;
                      dx_dr[sdf] = 0.0;
                      dx_ds[sdf] = 0.0;
                      for (int k = 0; k < nsn; ++k) {
                        Xp[sdf] += Hm[k] * Xm[sdf*nsn + k];
                        dx_dr[sdf] += dHm[k] * Xm[sdf*nsn + k];
                        if (npd == 2) {
                          dx_ds[sdf] += dHm[nsn + k] * Xm[sdf*nsn + k];
                        }
                      }
                    }

                    if(nsd == 2) {
                      normal[0] = dx_dr[1];
                      normal[1] = -dx_dr[0];
                      normal[2] = 0.0;
                      dx_dr[2] = 0.0;
                      dx_ds[2] = 0.0;
                    }
                    else if (nsd == 3) {
                      normal[0] = dx_dr[1]*dx_ds[2] - dx_dr[2]*dx_ds[1];
                      normal[1] = dx_dr[2]*dx_ds[0] - dx_dr[0]*dx_ds[2];
                      normal[2] = dx_dr[0]*dx_ds[1] - dx_dr[1]*dx_ds[0];
                    }

                    const double normalLength = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
                    normal[0] /= normalLength;
                    normal[1] /= normalLength;
                    normal[2] /= normalLength;

                    d = 0.0;
                    for (int sdf = 0; sdf < nsd; ++sdf) {
                      b1 += dx_dr[sdf]*(Xg[sdf] - Xp[sdf]);
                      A11 += dx_dr[sdf]*dx_dr[sdf];

                      if (npd == 2) {
                        b2 += dx_ds[sdf]*(Xg[sdf] - Xp[sdf]);
                        A22 += dx_ds[sdf]*dx_ds[sdf];
                        A12 += dx_dr[sdf]*dx_ds[sdf];
                      }

                      d -= (Xg[sdf] - Xp[sdf]) * normal[sdf];
                    }

                    double recDetA;
                    double invA11;
                    double invA22;
                    double invA12;
                    double dr;
                    double ds;

                    if (npd == 1) {
                      invA11 = 1 / A11;
                      dr = invA11*b1;
                      r += dr;
                      dr_norm = dr;
                    }

                    if (npd == 2) {
                      recDetA = 1 / (A11*A22 - A12*A12);
                      invA11 = recDetA * A22;
                      invA22 = recDetA * A11;
                      invA12 = -recDetA * A12;
                      dr = invA11*b1 + invA12*b2;
                      ds = invA12*b1 + invA22*b2;

                      r += dr;
                      s += ds;
                      dr_norm = sqrt(dr*dr + ds*ds);
                    }

                    niter++;
                  } while (dr_norm > 1e-5 && niter < max_niter);


                  if (niter >= max_niter) {
                    std::cout << "Fatal error: Local contact search do NOT converge." << std::endl;
                  }

                  if (fabs(r)  > 1 || fabs(s) > 1) {
                    std::cout << "Fatal error: Local contact search converges to point outside the element." << std::endl;
                  }


                  if (d > GPs[(nsd + 2)*n*ngp + v] && d < 20.0) {
                    GPs[(nsd       + 2)*n*ngp + v] = d;      // store gap (negative value means open gap)

                  if(d >= -20.0) { // "positive" zero
                    GPs[(nsd + npd + 3)*n*ngp + v] = 1.0;    // set gausspoint to active state
                  }
                  GPs[(nsd + npd + 4)*n*ngp + v] = el + 1; // set master element
                  GPs[(nsd + npd + 5)*n*ngp + v] = sg + 1; // set master segment

                  // Update Xi_m
                  GPs[(nsd       + 3)*n*ngp + v] = r;
                  if (npd == 2) {
                    GPs[(nsd     + 4)*n*ngp + v] = s;
                  }
                }

                /*
                else {
                GPs[(nsd + 2)*n*ngp + v] = FLT_MAX;    // init gap
                for (int pdf = 0; pdf < npd; ++pdf) {
                GPs[(nsd + 3 + pdf)*n*ngp + v] = 0.0; // Xi_m
              }
              GPs[(nsd + npd + 3)*n*ngp + v] = 0;       // init is NO active
              GPs[(nsd + npd + 4)*n*ngp + v] = 0;       // master element
              GPs[(nsd + npd + 5)*n*ngp + v] = 0;       // master segment
              GPs[(nsd + npd + 6)*n*ngp + v] = 0;       // is stick

              for (int pdf = 0; pdf < nsd-1; ++pdf) {
              GPs[(nsd + npd + 7 + pdf)*n*ngp + v] = 0.0; // tangent traction components
            }
            for (int pdf = 0; pdf < nsd-1; ++pdf) {
            GPs[(nsd + 2*npd + 7 + pdf)*n*ngp + v] = 0.0; // Xi0_m
          }
        }
        */

      } // if d is less then

    } // if projection is inside the segment
    v = next[v];
  } // while
} // i0
} // i1
}	// i2
} // loop over triangles
} // loop over elements

delete[] segmentNodesID;
delete[] Xm;
delete[] Xmin;
delete[] Xmax;
delete[] Hm;
delete[] dHm;
}
