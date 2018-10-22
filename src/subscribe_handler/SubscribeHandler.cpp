#include <mrs_lib/SubscribeHandler.h>

SubscribeHandler_base::SubscribeHandler_base(
  ros::NodeHandle& nh,
  ros::Duration no_message_timeout,
  const std::string& topic_name,
  const std::string& node_name
  )
  : m_no_message_timeout(no_message_timeout),
    m_topic_name(topic_name),
    m_node_name(node_name),
    m_got_data(false),
    m_new_data(false),
    m_last_msg_received(ros::Time::now())
{
  if (no_message_timeout != mrs_lib::no_timeout)
    m_timeout_check_timer = nh.createTimer(no_message_timeout, &SubscribeHandler_base::check_timeout, this);
}
  
void SubscribeHandler_base::check_timeout([[maybe_unused]] const ros::TimerEvent& evt)
{
  ros::Duration since_msg = (ros::Time::now() - m_last_msg_received);
  std::lock_guard<std::mutex> lck(m_last_msg_received_mtx);
  if (since_msg > m_no_message_timeout)
  {
    m_ok = false;
    const std::string msg = "Did not receive any message from topic '" + m_sub.getTopic()
                          + "' for " + std::to_string(since_msg.toSec())
                          + "s (" + std::to_string(m_sub.getNumPublishers()) + " publishers on this topic)";

    if (m_node_name.empty())
      ROS_ERROR_STREAM(msg);
    else
      ROS_ERROR_STREAM("[" << m_node_name << "]: " << msg);
  }
}

bool SubscribeHandler_base::ok()
{
  return m_ok;
}

bool SubscribeHandler_base::has_data()
{
  return m_got_data;
}

bool SubscribeHandler_base::new_data()
{
  return m_new_data;
}

bool SubscribeHandler_base::used_data()
{
  return m_got_data && !m_new_data;
}


