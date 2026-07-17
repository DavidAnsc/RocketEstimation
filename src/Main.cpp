#include <iostream>
#include <cmath>
#include "Constants.h"

static double getNoseConeDragMomentum(double duration, double avgVelocity, double baseDiameter, double dragCoefficient) {
  double area = std::pow((baseDiameter / 2), 2) * Constants::pi;
  printf("area is %.2f\n", area);
  double Fd = 0.5 * dragCoefficient * Constants::airDensity * std::pow(avgVelocity, 2) * area;
  printf("air drag force is %.2f\n", Fd);
  return -Fd * duration;
}
static double getNoseConeDragForce(double avgVelocity, double baseDiameter, double dragCoefficient) {
  double area = std::pow((baseDiameter / 2), 2) * Constants::pi;
  printf("area is %.2f\n", area);
  double Fd = 0.5 * dragCoefficient * Constants::airDensity * std::pow(avgVelocity, 2) * area;
  printf("air drag force is %.2f\n", Fd);
  return -Fd;
}

int main() {
  double rocketMass {};
  double engMass {};
  double prplMass {};
  double engBurnTime {};
  double engMomentum {};
  double noseConeD {};
  double dragCoefficient {};

  std::cout << "pls enter rocket mass (kg): ";
  std::cin >> rocketMass;
  std::cout << "\n CONFIRM: rocket mass -> " << rocketMass << "kg" << std::endl;

  std::cout << "pls enter engine burn time (s): ";
  std::cin >> engBurnTime;
  std::cout << "\n CONFIRM: engine burn time -> " << engBurnTime << "s" << std::endl;

  std::cout << "pls enter engine total impulse / momentum (kgm/s): ";
  std::cin >> engMomentum;
  std::cout << "\n CONFIRM: engine momentum -> " << engMomentum << "kgm/s" << std::endl;

  std::cout << "pls enter propellant mass (kg): ";
  std::cin >> prplMass;
  std::cout << "\n CONFIRM: propellant mass -> " << prplMass << "kg" << std::endl;

  std::cout << "pls enter nose cone diameter (m): ";
  std::cin >> noseConeD;
  std::cout << "\n CONFIRM: nose cone diameter -> " << noseConeD << "m" << std::endl;

  std::cout << "pls enter nose cone drag coefficient: ";
  std::cin >> dragCoefficient;
  std::cout << "\n CONFIRM: nose cone darg coefficient -> " << dragCoefficient << std::endl;

  double F_g_initial = -(rocketMass - prplMass/2) * Constants::g;
  double P_g_initial = engBurnTime * F_g_initial;
  printf("Fg is %.2f\n", F_g_initial);

  double P_t_initial = P_g_initial + engMomentum;
  printf("P_total_initial = %.2f + %.2f = %.2f\n", P_g_initial, engMomentum, P_t_initial);
  double V_initial {};
  double P_air_drag {};

  size_t i = 0;
  do {
    V_initial = (P_t_initial + P_air_drag) / (rocketMass - prplMass);
    printf("velocity is %.2f\n", V_initial);
    P_air_drag = getNoseConeDragMomentum(engBurnTime, V_initial / 1.732, noseConeD, dragCoefficient);
    // we need to get the avg drag, not avg velocity, that's why we don't use V_initial / 2.
    printf("P_air_drag is %f\n", P_air_drag);
    ++i;
  } while (i < 5);
  V_initial = (P_t_initial + P_air_drag) / (rocketMass - prplMass);

  double D_burn = (V_initial / 2) * engBurnTime;

  double F_g_late = -(rocketMass - prplMass) * Constants::g;
  double F_d_late = getNoseConeDragForce(V_initial / 1.732, noseConeD, dragCoefficient);;
  double A_g_late = F_g_late / (rocketMass - prplMass);
  double A_d_late = F_d_late / (rocketMass - prplMass);;

  double T_coast {};
  printf("A_d is %.5fm/s^2\n", A_d_late);
  T_coast = -V_initial / (A_g_late + A_d_late);

  double D_coast = (V_initial / 2) * T_coast;

  std::cout << "** burnout velocity (m/s): " << V_initial << " **" << std::endl;
  std::cout << "** travel time (m/s): " << T_coast + engBurnTime << " **" << std::endl;
  std::cout << "** apogee (m): " << D_burn + D_coast << " **" << std::endl;

  return 0;
}