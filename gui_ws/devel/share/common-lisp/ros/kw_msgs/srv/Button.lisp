; Auto-generated. Do not edit!


(cl:in-package kw_msgs-srv)


;//! \htmlinclude Button-request.msg.html

(cl:defclass <Button-request> (roslisp-msg-protocol:ros-message)
  ((btn
    :reader btn
    :initarg :btn
    :type cl:string
    :initform ""))
)

(cl:defclass Button-request (<Button-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Button-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Button-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name kw_msgs-srv:<Button-request> is deprecated: use kw_msgs-srv:Button-request instead.")))

(cl:ensure-generic-function 'btn-val :lambda-list '(m))
(cl:defmethod btn-val ((m <Button-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kw_msgs-srv:btn-val is deprecated.  Use kw_msgs-srv:btn instead.")
  (btn m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Button-request>) ostream)
  "Serializes a message object of type '<Button-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'btn))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'btn))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Button-request>) istream)
  "Deserializes a message object of type '<Button-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'btn) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'btn) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Button-request>)))
  "Returns string type for a service object of type '<Button-request>"
  "kw_msgs/ButtonRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Button-request)))
  "Returns string type for a service object of type 'Button-request"
  "kw_msgs/ButtonRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Button-request>)))
  "Returns md5sum for a message object of type '<Button-request>"
  "3da1caf570615076e9b296a945eee01a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Button-request)))
  "Returns md5sum for a message object of type 'Button-request"
  "3da1caf570615076e9b296a945eee01a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Button-request>)))
  "Returns full string definition for message of type '<Button-request>"
  (cl:format cl:nil "string btn~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Button-request)))
  "Returns full string definition for message of type 'Button-request"
  (cl:format cl:nil "string btn~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Button-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'btn))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Button-request>))
  "Converts a ROS message object to a list"
  (cl:list 'Button-request
    (cl:cons ':btn (btn msg))
))
;//! \htmlinclude Button-response.msg.html

(cl:defclass <Button-response> (roslisp-msg-protocol:ros-message)
  ((flag
    :reader flag
    :initarg :flag
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass Button-response (<Button-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Button-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Button-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name kw_msgs-srv:<Button-response> is deprecated: use kw_msgs-srv:Button-response instead.")))

(cl:ensure-generic-function 'flag-val :lambda-list '(m))
(cl:defmethod flag-val ((m <Button-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kw_msgs-srv:flag-val is deprecated.  Use kw_msgs-srv:flag instead.")
  (flag m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Button-response>) ostream)
  "Serializes a message object of type '<Button-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'flag) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Button-response>) istream)
  "Deserializes a message object of type '<Button-response>"
    (cl:setf (cl:slot-value msg 'flag) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Button-response>)))
  "Returns string type for a service object of type '<Button-response>"
  "kw_msgs/ButtonResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Button-response)))
  "Returns string type for a service object of type 'Button-response"
  "kw_msgs/ButtonResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Button-response>)))
  "Returns md5sum for a message object of type '<Button-response>"
  "3da1caf570615076e9b296a945eee01a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Button-response)))
  "Returns md5sum for a message object of type 'Button-response"
  "3da1caf570615076e9b296a945eee01a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Button-response>)))
  "Returns full string definition for message of type '<Button-response>"
  (cl:format cl:nil "bool flag~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Button-response)))
  "Returns full string definition for message of type 'Button-response"
  (cl:format cl:nil "bool flag~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Button-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Button-response>))
  "Converts a ROS message object to a list"
  (cl:list 'Button-response
    (cl:cons ':flag (flag msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'Button)))
  'Button-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'Button)))
  'Button-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Button)))
  "Returns string type for a service object of type '<Button>"
  "kw_msgs/Button")