; Auto-generated. Do not edit!


(cl:in-package kw_msgs-msg)


;//! \htmlinclude CarrotFeedback.msg.html

(cl:defclass <CarrotFeedback> (roslisp-msg-protocol:ros-message)
  ((remaining
    :reader remaining
    :initarg :remaining
    :type cl:integer
    :initform 0)
   (current
    :reader current
    :initarg :current
    :type cl:integer
    :initform 0))
)

(cl:defclass CarrotFeedback (<CarrotFeedback>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CarrotFeedback>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CarrotFeedback)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name kw_msgs-msg:<CarrotFeedback> is deprecated: use kw_msgs-msg:CarrotFeedback instead.")))

(cl:ensure-generic-function 'remaining-val :lambda-list '(m))
(cl:defmethod remaining-val ((m <CarrotFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kw_msgs-msg:remaining-val is deprecated.  Use kw_msgs-msg:remaining instead.")
  (remaining m))

(cl:ensure-generic-function 'current-val :lambda-list '(m))
(cl:defmethod current-val ((m <CarrotFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kw_msgs-msg:current-val is deprecated.  Use kw_msgs-msg:current instead.")
  (current m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CarrotFeedback>) ostream)
  "Serializes a message object of type '<CarrotFeedback>"
  (cl:let* ((signed (cl:slot-value msg 'remaining)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'current)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CarrotFeedback>) istream)
  "Deserializes a message object of type '<CarrotFeedback>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'remaining) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'current) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CarrotFeedback>)))
  "Returns string type for a message object of type '<CarrotFeedback>"
  "kw_msgs/CarrotFeedback")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CarrotFeedback)))
  "Returns string type for a message object of type 'CarrotFeedback"
  "kw_msgs/CarrotFeedback")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CarrotFeedback>)))
  "Returns md5sum for a message object of type '<CarrotFeedback>"
  "36a3eb3d921af7db8b535add2ff4e974")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CarrotFeedback)))
  "Returns md5sum for a message object of type 'CarrotFeedback"
  "36a3eb3d921af7db8b535add2ff4e974")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CarrotFeedback>)))
  "Returns full string definition for message of type '<CarrotFeedback>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define the feedback~%int64 remaining~%int64 current~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CarrotFeedback)))
  "Returns full string definition for message of type 'CarrotFeedback"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define the feedback~%int64 remaining~%int64 current~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CarrotFeedback>))
  (cl:+ 0
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CarrotFeedback>))
  "Converts a ROS message object to a list"
  (cl:list 'CarrotFeedback
    (cl:cons ':remaining (remaining msg))
    (cl:cons ':current (current msg))
))
