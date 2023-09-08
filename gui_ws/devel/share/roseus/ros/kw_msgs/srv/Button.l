;; Auto-generated. Do not edit!


(when (boundp 'kw_msgs::Button)
  (if (not (find-package "KW_MSGS"))
    (make-package "KW_MSGS"))
  (shadow 'Button (find-package "KW_MSGS")))
(unless (find-package "KW_MSGS::BUTTON")
  (make-package "KW_MSGS::BUTTON"))
(unless (find-package "KW_MSGS::BUTTONREQUEST")
  (make-package "KW_MSGS::BUTTONREQUEST"))
(unless (find-package "KW_MSGS::BUTTONRESPONSE")
  (make-package "KW_MSGS::BUTTONRESPONSE"))

(in-package "ROS")





(defclass kw_msgs::ButtonRequest
  :super ros::object
  :slots (_btn ))

(defmethod kw_msgs::ButtonRequest
  (:init
   (&key
    ((:btn __btn) "")
    )
   (send-super :init)
   (setq _btn (string __btn))
   self)
  (:btn
   (&optional __btn)
   (if __btn (setq _btn __btn)) _btn)
  (:serialization-length
   ()
   (+
    ;; string _btn
    4 (length _btn)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _btn
       (write-long (length _btn) s) (princ _btn s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _btn
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _btn (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass kw_msgs::ButtonResponse
  :super ros::object
  :slots (_flag ))

(defmethod kw_msgs::ButtonResponse
  (:init
   (&key
    ((:flag __flag) nil)
    )
   (send-super :init)
   (setq _flag __flag)
   self)
  (:flag
   (&optional (__flag :null))
   (if (not (eq __flag :null)) (setq _flag __flag)) _flag)
  (:serialization-length
   ()
   (+
    ;; bool _flag
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _flag
       (if _flag (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _flag
     (setq _flag (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass kw_msgs::Button
  :super ros::object
  :slots ())

(setf (get kw_msgs::Button :md5sum-) "3da1caf570615076e9b296a945eee01a")
(setf (get kw_msgs::Button :datatype-) "kw_msgs/Button")
(setf (get kw_msgs::Button :request) kw_msgs::ButtonRequest)
(setf (get kw_msgs::Button :response) kw_msgs::ButtonResponse)

(defmethod kw_msgs::ButtonRequest
  (:response () (instance kw_msgs::ButtonResponse :init)))

(setf (get kw_msgs::ButtonRequest :md5sum-) "3da1caf570615076e9b296a945eee01a")
(setf (get kw_msgs::ButtonRequest :datatype-) "kw_msgs/ButtonRequest")
(setf (get kw_msgs::ButtonRequest :definition-)
      "string btn
---
bool flag
")

(setf (get kw_msgs::ButtonResponse :md5sum-) "3da1caf570615076e9b296a945eee01a")
(setf (get kw_msgs::ButtonResponse :datatype-) "kw_msgs/ButtonResponse")
(setf (get kw_msgs::ButtonResponse :definition-)
      "string btn
---
bool flag
")



(provide :kw_msgs/Button "3da1caf570615076e9b296a945eee01a")


