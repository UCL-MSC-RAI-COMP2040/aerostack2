/*!*******************************************************************************************
 *  \file       trajectory_motion.hpp
 *  \brief      this file contains the definition of the TrajectoryMotion class
 *  \authors    Miguel Fernández Cortizas
 *              Pedro Arias Pérez
 *              David Pérez Saura
 *              Rafael Pérez Seguí
 *
 *  \copyright  Copyright (c) 2022 Universidad Politécnica de Madrid
 *              All Rights Reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ********************************************************************************/

#include "motion_reference_handlers/trajectory_motion.hpp"

namespace as2 {
namespace motionReferenceHandlers {
TrajectoryMotion::TrajectoryMotion(as2::Node *node_ptr) : BasicMotionReferenceHandler(node_ptr) {
  desired_control_mode_.yaw_mode        = as2_msgs::msg::ControlMode::YAW_ANGLE;
  desired_control_mode_.control_mode    = as2_msgs::msg::ControlMode::TRAJECTORY;
  desired_control_mode_.reference_frame = as2_msgs::msg::ControlMode::LOCAL_ENU_FRAME;
}

bool TrajectoryMotion::sendTrajectoryCommandWithYawAngle(const std::string &frame_id,
                                                         const float &x,
                                                         const float &y,
                                                         const float &z,
                                                         const float &yaw_angle,
                                                         const float &vx,
                                                         const float &vy,
                                                         const float &vz,
                                                         const float &ax,
                                                         const float &ay,
                                                         const float &az) {
  if (frame_id == "") {
    RCLCPP_ERROR(this->node_ptr_->get_logger(), "Frame id is empty");
    return false;
  }

  this->command_trajectory_msg_.header.frame_id = frame_id;
  this->command_trajectory_msg_.header.stamp    = this->node_ptr_->now();

  this->command_trajectory_msg_.yaw_angle = yaw_angle;

  this->command_trajectory_msg_.position.x = x;
  this->command_trajectory_msg_.position.y = y;
  this->command_trajectory_msg_.position.z = z;

  this->command_trajectory_msg_.twist.x = vx;
  this->command_trajectory_msg_.twist.y = vy;
  this->command_trajectory_msg_.twist.z = vz;

  this->command_trajectory_msg_.acceleration.x = ax;
  this->command_trajectory_msg_.acceleration.y = ay;
  this->command_trajectory_msg_.acceleration.z = az;

  return this->sendTrajectoryCommand();
}

bool TrajectoryMotion::sendTrajectoryCommandWithYawAngle(const std::string &frame_id,
                                                         const std::vector<double> &positions,
                                                         const std::vector<double> &velocities,
                                                         const std::vector<double> &accelerations) {
  return this->sendTrajectoryCommandWithYawAngle(
      frame_id, positions[0], positions[1], positions[2], positions[3], velocities[0],
      velocities[1], velocities[2], accelerations[0], accelerations[1], accelerations[2]);
}

}  // namespace motionReferenceHandlers
}  // namespace as2