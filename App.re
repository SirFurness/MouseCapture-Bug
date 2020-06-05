open Revery;
open Revery.UI;
open Revery.UI.Components;

type reducerState = {state: string};

type action =
  | Enter
  | Leave;

let reducer = (action, state) =>
  switch (action) {
  | Enter => {state: "entered"}
  | Leave => {state: "left"}
  };

let%component reducerVersion = () => {
  let%hook (aHook, dispatch) =
    Hooks.reducer(~initialState={state: "default"}, reducer);

  let%hook (captureMouse, captureState) =
    Hooks.mouseCapture(
      ~onMouseUp=
        (_state, _evt) => {
          print_endline(aHook.state);
          None;
        },
      (),
    );

  let onMouseDown = _evt => captureMouse();

  let onMouseEnter = _evt => dispatch(Enter);
  let onMouseLeave = _evt => dispatch(Leave);

  <View onMouseDown onMouseEnter onMouseLeave>
    <Text
      style=Style.[fontFamily("Roboto-Regular.ttf"), fontSize(20.)]
      text="reducer version!"
    />
  </View>;
};

let%component stateVersion = () => {
  let%hook (aHook, setAHook) = Hooks.state("default");

  let%hook (captureMouse, captureState) =
    Hooks.mouseCapture(
      ~onMouseUp=
        (_state, _evt) => {
          print_endline(aHook);
          None;
        },
      (),
    );

  let onMouseDown = _evt => captureMouse();

  let onMouseEnter = _evt => setAHook(_ => "entered");
  let onMouseLeave = _evt => setAHook(_ => "left");

  <View onMouseDown onMouseEnter onMouseLeave>
    <Text
      style=Style.[fontFamily("Roboto-Regular.ttf"), fontSize(20.)]
      text="state version!"
    />
  </View>;
};

let main = () => {
  <View style=Style.[flexDirection(`Column)]>
    <stateVersion />
    <reducerVersion />
  </View>;
};

let init = app => {
  Revery.App.initConsole();

  Timber.App.enable();
  Timber.App.setLevel(Timber.Level.perf);

  let win = App.createWindow(app, "Welcome to Revery!");

  let _: Revery.UI.renderFunction = UI.start(win, <main />);
  ();
};

App.start(init);
