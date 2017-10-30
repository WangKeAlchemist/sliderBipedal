import numpy as np
import vrep

try:
    # close any open connections
    vrep.simxFinish(-1)
    # Connect to the V-REP continuous server
    clientID = vrep.simxStart('127.0.0.1', 19997, True, True, 500, 5)

    if clientID != -1: # if we connected successfully
        print ('Connected to remote API server')

        # --------------------- Setup the simulation

        vrep.simxSynchronous(clientID,True)

        joint_names = ['Revolute_joint_left', 'Revolute_joint_right']
        # joint target velocities discussed below
        # joint_target_velocities = np.ones(len(joint_names)) * 10000.0

        # get the handles for each joint and set up streaming
        joint_handles = [vrep.simxGetObjectHandle(clientID,
            name, vrep.simx_opmode_blocking)[1] for name in joint_names]

        # get handle for target and set up streaming
        # _, target_handle = vrep.simxGetObjectHandle(clientID,
        #                 'target', vrep.simx_opmode_blocking)

        dt = .001
        vrep.simxSetFloatingParameter(clientID,
                vrep.sim_floatparam_simulation_time_step,
                dt, # specify a simulation time step
                vrep.simx_opmode_oneshot)

        # --------------------- Start the simulation

        # start our simulation in lockstep with our code
        vrep.simxStartSimulation(clientID,
                vrep.simx_opmode_blocking)

        count = 0
        while count < 1: # run for 1 simulated second

            for ii,joint_handle in enumerate(joint_handles):
            	vrep.simxSetJointPosition(clientID, joint_handle, 1, vrep.simx_opmode_oneshot)#vrep.simx_opmode_blocking

				# vrep.simxSetJointPosition(clientID, joint_handle, 1, vrep.simx_opmode_blocking)

            # move simulation ahead one time step
            vrep.simxSynchronousTrigger(clientID)
            count += dt
            print(count)

        # stop the simulation
        vrep.simxStopSimulation(clientID, vrep.simx_opmode_blocking)

        # Before closing the connection to V-REP,
        #make sure that the last command sent out had time to arrive.
        vrep.simxGetPingTime(clientID)

        # Now close the connection to V-REP:
        vrep.simxFinish(clientID)
    else:
        raise Exception('Failed connecting to remote API server')

finally:

    # stop the simulation
    vrep.simxStopSimulation(clientID, vrep.simx_opmode_blocking)

    # Before closing the connection to V-REP,
    # make sure that the last command sent out had time to arrive.
    vrep.simxGetPingTime(clientID)

    # Now close the connection to V-REP:
    vrep.simxFinish(clientID)
    print('connection closed...')