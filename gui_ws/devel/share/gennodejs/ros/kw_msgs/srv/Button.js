// Auto-generated. Do not edit!

// (in-package kw_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class ButtonRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.btn = null;
    }
    else {
      if (initObj.hasOwnProperty('btn')) {
        this.btn = initObj.btn
      }
      else {
        this.btn = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ButtonRequest
    // Serialize message field [btn]
    bufferOffset = _serializer.string(obj.btn, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ButtonRequest
    let len;
    let data = new ButtonRequest(null);
    // Deserialize message field [btn]
    data.btn = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.btn);
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'kw_msgs/ButtonRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a39a9e07f6787f3ce35e3cfe1002e17f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string btn
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ButtonRequest(null);
    if (msg.btn !== undefined) {
      resolved.btn = msg.btn;
    }
    else {
      resolved.btn = ''
    }

    return resolved;
    }
};

class ButtonResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.flag = null;
    }
    else {
      if (initObj.hasOwnProperty('flag')) {
        this.flag = initObj.flag
      }
      else {
        this.flag = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ButtonResponse
    // Serialize message field [flag]
    bufferOffset = _serializer.bool(obj.flag, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ButtonResponse
    let len;
    let data = new ButtonResponse(null);
    // Deserialize message field [flag]
    data.flag = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'kw_msgs/ButtonResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '24842bc754e0f5cc982338eca1269251';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool flag
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ButtonResponse(null);
    if (msg.flag !== undefined) {
      resolved.flag = msg.flag;
    }
    else {
      resolved.flag = false
    }

    return resolved;
    }
};

module.exports = {
  Request: ButtonRequest,
  Response: ButtonResponse,
  md5sum() { return '3da1caf570615076e9b296a945eee01a'; },
  datatype() { return 'kw_msgs/Button'; }
};
