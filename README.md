# WeGo Scout mini Exercise
---
## 💻 팀원
<table>
    <tr height="150px">
        <td align="center" width="130px">
            <a href="https://github.com/syw2045"><img height="100px" width="100px" src="https://avatars.githubusercontent.com/u/81313733?v=4"></a>
            <br/>
            <a href="https://github.com/syw2045">SSong</a>
        </td>
        <td align="center" width="130px">
            <a href="[https://github.com/SaltnLight-pet"><img height="100px" width="100px" src="https://avatars.githubusercontent.com/u/142612336?v=4"></a>
            <br/>
            <a href="https://github.com/SaltnLight-pet">SaltnLight-pet</a>
        <td align="center" width="130px">
            <a href="https://github.com/Heesun0-0"><img height="100px" width="100px" src="https://avatars.githubusercontent.com/u/125299969?v=4"/></a>
            <br/>
            <a href="https://github.com/Heesun0-0">Heesun0-0</a>
        <td align="center" width="130px">
            <a href="https://github.com/JunseoMin"><img height="100px" width="100px" src="https://avatars.githubusercontent.com/u/114414158?v=4"/></a>
            <br/>
            <a href="https://github.com/JunseoMin">JunseoMin</a>
        </td>
    </tr>
</table>

--- 

## Enviroment

|OS|Version|
|:---:|:---:|
|Ubuntu|20.04.6 LTS|
|ROS|Noetic|


|HW|Version|
|:---:|:---:|
|ROBOT|WeGo-ST MINI|


## SLAM
### ROBOT
```bash
rosrun scout_bringup bringup_can2usb.bash
roslaunch kw robot_bringup.launch
roslaunch gmapping slam_gmapping_pr2.launch
```
### LOCAL
```bash
roslaunch display gmapping_display.launch
```
![SLAM](https://github.com/KW-BBIBBI/Food-Delivery/assets/81313733/500b42f8-92b0-400b-b0bc-ee13bc765c50)


## Navigation
### ROBOT
```bash
rosrun scout_bringup bringup_can2usb.bash
roslaunch kw robot_bringup.launch
roslaunch kw navigation.launch
```
### LOCAL
```bash
roslaunch display navigation_display.launch
```

![NAVI](https://github.com/KW-BBIBBI/Food-Delivery/assets/81313733/f256cf20-8b09-485f-92d6-59bc07a8c44a)

## MultiwayPoint

### ROBOT
```bash
rosrun scout_bringup bringup_can2usb.bash
roslaunch kw robot_bringup.launch
roslaunch kw navigation.launch
rosrun multiwaypoints follow_waypoint
```

### LOCAL
```bash
roslaunch display navigation_display.launch
```

<p align="left"><img src="https://github.com/KW-BBIBBI/Food-Delivery/assets/125299969/0978ba11-3dcf-4232-9b1d-62c020fd68d2" height="228" width="400">    <img src="https://github.com/KW-BBIBBI/Food-Delivery/assets/81313733/76d2d5d2-0305-4f02-ab34-566cc73b73fd" height="228" width="600""></p>

## Obstacle Detector
### ROBOT
```bash
rosrun scout_bringup bringup_can2usb.bash
roslaunch kw robot_pointcloud.launch
roslaunch kw navigation.launch
```
### LOCAL
```bash
roslaunch display obstacle_display.launch
```
<p align="left"><img src="https://github.com/KW-BBIBBI/Food-Delivery/assets/142612336/0542322d-380d-4b8e-bd4e-b532506050e0" height="228" width="400">    <img src="https://github.com/KW-BBIBBI/Food-Delivery/assets/142612336/bca0b58e-2e9c-45a8-ba10-6707451cf0f9" height="228" width="400""></p>

## GUI
### ROBOT
```bash
rosrun scout_bringup bringup_can2usb.bash
roslaunch kw final_.launch
```

### LOCAL
```bash
rosrun kw_gui kw_gui
```

<p align="left"><img src="https://github.com/KW-BBIBBI/Food-Delivery/assets/81313733/e885ac1a-6e22-49e3-82bb-04008456b80c" height="280" width="250">    <img src="https://github.com/KW-BBIBBI/Food-Delivery/assets/81313733/f45d03d5-b8ae-4936-8335-7e987cc19754" height="280" width="550""></p>