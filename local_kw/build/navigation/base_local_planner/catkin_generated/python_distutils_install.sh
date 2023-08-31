#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/pet/Food-Delivery/local_kw/src/navigation/base_local_planner"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/pet/Food-Delivery/local_kw/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/pet/Food-Delivery/local_kw/install/lib/python3/dist-packages:/home/pet/Food-Delivery/local_kw/build/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/pet/Food-Delivery/local_kw/build" \
    "/usr/bin/python3" \
    "/home/pet/Food-Delivery/local_kw/src/navigation/base_local_planner/setup.py" \
     \
    build --build-base "/home/pet/Food-Delivery/local_kw/build/navigation/base_local_planner" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/pet/Food-Delivery/local_kw/install" --install-scripts="/home/pet/Food-Delivery/local_kw/install/bin"
