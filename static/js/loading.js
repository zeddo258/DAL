const Character = ({ animation, armPath }) => {
  const characterClass = `character -${animation}`;
  return (
    React.createElement("svg", { className: characterClass, xmlns: "http://www.w3.org/2000/svg", viewBox: "0 0 300 400" },
      React.createElement("circle", { className: "character__eye -eye-r", cx: "87.59", cy: "134.46", r: "5.12" }),
      React.createElement("g", { id: "body" },
        React.createElement("circle", { className: "character__body -part-1", cx: "140.71", cy: "122.62", r: "42.88" }),
        React.createElement("circle", { className: "character__body -part-2", cx: "166.95", cy: "141.82", r: "42.88" }),
        React.createElement("circle", { className: "character__body -part-3", cx: "191.26", cy: "173.82", r: "42.88" }),
        React.createElement("circle", { className: "character__body", cx: "197.02", cy: "335.1", r: "42.88" }),
        React.createElement("circle", { className: "character__body", cx: "197.02", cy: "295.42", r: "42.88" }),
        React.createElement("circle", { className: "character__body", cx: "206.62", cy: "216.06", r: "42.88" }),
        React.createElement("circle", { className: "character__body", cx: "205.98", cy: "258.94", r: "42.88" })),

      React.createElement("circle", { className: "character__eye -eye-l-extra", cx: "87.59", cy: "134.46", r: "5.12" }),
      React.createElement("circle", { className: "character__eye -eye-l", cx: "115.11", cy: "134.46", r: "5.12" })));


};

// Left arm component
const ArmLeft = ({ animation, armPath }) =>
  React.createElement("svg", { className: "arm", xmlns: "http://www.w3.org/2000/svg", viewBox: "0 0 300 400" },
    animation === 'stressed' && React.createElement("path", { className: "arm-typing-left", d: armPath }),

  );



// Right arm component
const ArmRight = ({ animation, armPath }) =>
  React.createElement("svg", { className: "arm", xmlns: "http://www.w3.org/2000/svg", viewBox: "0 0 300 400" },
    animation === 'stressed' && React.createElement("path", { className: "arm-typing-right", d: armPath }),

  );



// Computer component
const Computer = ({ animation }) => {
  const computerClass = `computer -${animation}`;
  return (
    React.createElement("svg", { className: computerClass, xmlns: "http://www.w3.org/2000/svg", viewBox: "0 0 82 55" },
      React.createElement("polygon", { className: "computer__keyboard", points: "29,42.5 81,51.5 45,55.5 30,49.5 " }),
      React.createElement("path", { className: "computer__keyboard", d: "M80.3,55.5H45.7c-0.9,0-1.7-0.7-1.7-1.7v-0.7c0-0.9,0.7-1.7,1.7-1.7h34.7c0.9,0,1.7,0.7,1.7,1.7v0.7 C82,54.8,81.2,55.5,80.3,55.5z" }),

      React.createElement("path", { className: "computer__screen", d: "M38.9,55.4l-27.3-6.3c-1.6-0.4-2.8-1.6-3.1-3.2l-8.4-41C-0.5,2.2,1.7-0.2,4.5,0l27.4,2.5 c1.8,0.2,3.3,1.5,3.7,3.3l8.3,44.8C44.4,53.6,41.8,56.1,38.9,55.4z" })));



};

// Table component
const Table = () =>
  React.createElement("svg", { className: "table", xmlns: "http://www.w3.org/2000/svg", viewBox: "0 0 530 160.1" },
    React.createElement("polygon", { points: "530,65.8 197.7,0 0,10.6 274.9,160.1 " }));



class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      animation: "stressed",
      armPath: "M 207 171",
      frequency: 3,
      amplitude: 0.1,
      xstart: 207,
      ystart: 171,
      length: 110,
      offset: 0,
      fps: 60
    };

    this.createCurve = this.createCurve.bind(this);
    this.setAnimation = this.setAnimation.bind(this);
    this.setConfig = this.setConfig.bind(this);
    this.updateArms = this.updateArms.bind(this);
    this.loop = this.loop.bind(this);
    this.loopref = null;


  }

  createCurve(x, offset, inverted = false) {
    const { frequency, ystart, xstart, amplitude } = this.state;
    const phase = inverted ? Math.sqrt(x * frequency) - offset : Math.sqrt(x * frequency) + offset;
    return ystart - Math.sin(phase) * (x - xstart) * amplitude;
  }

  updateArms() {
    const { ystart, xstart, length } = this.state;
    let x = xstart;
    let dataL = `M ${xstart} ${ystart}`;
    let dataR = `M ${xstart} ${ystart}`;

    while (x < xstart + length) {
      const newYL = this.createCurve(x, this.state.offset);
      const newYR = this.createCurve(x, this.state.offset, true);
      dataL = `${dataL} L ${x} ${newYL}`;
      dataR = `${dataR} L ${x} ${newYR}`;
      x += 1;
    }
    this.setState({
      armPathL: dataL,
      armPathR: dataR
    });

  }

  loop() {
    const { offset, animation, fps } = this.state;
    this.setState({
      offset: offset + 0.3
    });
    this.updateArms();
    this.loopRef = setTimeout(() => {
      requestAnimationFrame(this.loop);
    }, 100 / fps);
  }

  setAnimation(newAnimation, speed) {
    this.setState({
      animation: newAnimation,
      fps: speed || 60
    });

    if (newAnimation === "stressed") {
      clearTimeout(this.loopRef);
      requestAnimationFrame(this.loop);
    }
  }

  setConfig(e) {
    const type = e.target.name;
    console.log(type);
    this.setState({
      [type]: e.target.value
    });

  }

  render() {
    const { frequency, amplitude, animation } = this.state;
    return (
      React.createElement("div", { className: "app" },
        React.createElement("div", { className: "wrapper" },
          React.createElement(ArmLeft, { animation: this.state.animation, armPath: this.state.armPathL }),
          React.createElement(Character, { animation: this.state.animation }),
          React.createElement(ArmRight, { animation: this.state.animation, armPath: this.state.armPathR }),
          React.createElement(Table, null),
          React.createElement(Computer, { animation: this.state.animation })
        ),
        React.createElement("div", { className: "controls" },

        ),
        animation === 'stressed' &&
        React.createElement("div", { className: "sliders" })
      )
    );
  }
  componentDidMount() {
    this.updateArms();
    this.loop();
  }
}



document.querySelector('.post-btn').addEventListener('click', function () {
  // 獲取遮罩層（modal）容器
  const modalContainer = document.getElementById('modal-container');

  // 使用React來渲染你的動畫（或其他內容）到遮罩層（modal）中
  ReactDOM.render(
    React.createElement(App, null), // 這裡的App是你的React組件
    modalContainer
  );

  // 顯示遮罩層（modal）
  modalContainer.style.display = 'block';
});
