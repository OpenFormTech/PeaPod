# Aeroponics Subsystem

<img src="./assets/aeroponics_plumbing_diagram.png" width=80%>

# Assembly

## Assembly Notes

Review these before assembly.

- Applying Teflon Tape: [Tutorial](https://www.youtube.com/watch?v=f7mjyzfB9Ec)
- Assembling Compression Fittings: [Instructions](https://www.siouxchief.com/docs/default-source/technical-documents/installations/specialties/ander-lign-fittings-brass) (see pg. 2, Ander-Lign Universal Fittings)

## Materials

### Purchased

Refer to [the purchase BOM](./hardware/aeroponics_bom_purchase.csv).

### Tools

- Cutters (for tubing)
- Utility Knife (for Teflon)
- Pipe Wrench (for fittings)
- 12V Power Supply (for pump testing)

## Instructions

<!-- TODO: tubing lengths -->

> **NOTE**: Refer to the assembled photo below for orientations.

1. Cut a 30cm length of 3/8" PET tubing. Slide two hose clamps onto the tubing. Affix one end to the 3/4" Hose Female x 3/8" Barb fitting (**barb end**), and the other to the 3/8" *input* barb of the diaphragm pump (see photo). Secure one clamp firmly on each end.
3. Apply Teflon tape to the 3/8" Barb x 3/8" MPT Adapter (**MPT end**). Fit this adapter to the 1/2" x 3/8" FPT Coupling (**3/8" ends**). This assembly is now referred to as the *3/8"-1/2" Adapter*.
5. Cut a 30cm length of 3/8" PET tubing. Slide two hose clamps onto the tubing. Affix one end to the 3/8" *output* barb of the pump (see photo), and the other to the 3/8"-1/2" Adapter (**barb end**). Secure one clamp firmly on each end.
6. Cut a 30cm length of 1/4" OD PET tubing. Apply Teflon tape to the 1/4in. OD x 1/2in. MPT Compression Fitting Adapter (**MPT end**). *__DO NOT__ apply to the compression threads.* Assemble the compression fitting to the length of tubing. *__DO NOT__ over-tighten the compression nut.* Fit this adapter (**1/2" end**) to the 1/2" x 1/2" FPT Coupling. This assembly is now referred to as the *1/2"-1/4" OD Adapter*.
4. Apply Teflon tape to both 1/2" MPT ends of the accumulator tank. Affix the 3/8"-1/2" Adapter to the *input barb* of the accumulator tank. Affix the 1/2"-1/4" OD Adapter to the *output barb* of the accumulator tank.
5. Cut two 50cm lengths of 1/4" OD PET tubing. Insert the tubing from the 1/2"-1/4" OD Adapter into the push-connect input of the solenoid. Insert the first length of tubing into a) the push-connect output of the solenoid, and b) one of the "in-line" ends of a push-connect T-fitting. Insert the second length of tubing into a) the opposing "in-line" end of the push-connect T-fitting, and b) one end of a push-connect straight fitting.
6. Insert two nozzles into the open spots on the two push-connect fittings.

<img src="./assets/aeroponics_assembled.jpeg" width=80%>

# Testing

> NOTE: As this is a pressurized system, the following tests should be done *in order*. Following the execution of each testing protocol, return the subsystem to the state following the completion of the assembly.

## Leaks

**Protocol**: Detach the solenoid and subsequent components. Attach a standard garden hose to the input end of the system. Turn on the water gradually, checking for leaks at each connection.

**Validation**: No leaks observed at any connection.

**Failure Protocol**: Disassemble the failed connection(s). Remove existing Teflon. Reapply Teflon, and reassemble the connection(s). Ensure Teflon is applied properly, and each connection is appropriately secured.

## Priming

**Protocol**: Fill a bucket with contaminant- and debris-free water. Ensure the system is on level ground. Place the input end of the system in the bucket. Detach the solenoid from the preceding tubing section. Detach the subsequent tubing section from the T-fitting. Connect the tank output tubing section to the T-fitting. Apply 12V power to the pump. *Priming may take a minute or two.*

**Validation**: The pump is able to prime the system and expel all air.

**Failure Protocol**: Ensure the system is level and the system input is submerged. Ensure the pump is recieving power.

## Pressurization

**Protocol**: Same as [Priming](#priming).

**Validation**: The system pressurizes without failure or leak at any connection or component.

**Failure Protocols** (in increasing order of severity): 

1. *Leak*: Disassemble the failed connection(s). Remove existing Teflon. Reapply Teflon, and reassemble the connection(s). Ensure Teflon is applied properly, and each connection is appropriately secured.
2. *Component Failure*: Replace the failed component. Repeat Assembly.

## Nozzle Function

**Protocol**: Same as [Priming](#priming).

**Validation**: Nozzle flow is uninterrupted and consistent in rate over time. Droplet size is as expected and consistent, both over time and across the range of drople.

**Failure Protocol**: N/A

## Pump Auto-Shutoff

**Protocol**: Same as [Priming](#priming).

**Validation**: Pump shuts off automatically approximately one minute after priming is complete. Nozzle flow is uninterrupted. Pump turns back on automatically approximately one minute after having shut off.

**Failure Protocol**: N/A

<!-- TODO: pressure sensor for accuracy -->

<!-- TODO: solenoid function -->