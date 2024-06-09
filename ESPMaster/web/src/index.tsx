import { render } from 'preact';

import './style.css';
import { useEffect, useState } from 'preact/hooks';

export function App() {
	const [offsets, setOffsets] = useState<number[]>([0, 111, 222, 333, 444, 555, 666, 777, 888, 999, 1000, 1111, 1222, 1333, 1444, 1555])
	async function getAndSetOffsets() {
		const res = await fetch('/offset')
		const data = await res.json()
		setOffsets(data)
	}

	useEffect(() => {
		void getAndSetOffsets()
	}, [])

    async function handleFormSubmit(event: Event) {
        event.preventDefault(); // Prevent the default form submission
        const formData = new FormData(event.target as HTMLFormElement);
        await fetch('/offset', {
            method: 'POST',
            body: formData,
        });
		setTimeout(async () => {
			await getAndSetOffsets(); // Call getAndSetOffsets after form submission
		}, 1000);
    }

	return (
		<div class="content">
			<div class="card-grid">
				<form action="/" method="post" id="form">

					<div class="card">
						<p class="card-title">Text Alignment</p>
						<div class="line">
							<div class="inputWithLabel">
								<input type="radio" id="textleft" name="alignment" autocomplete="off" value="left" />
								<label for="textleft">left-aligned</label>
							</div>
							<div class="inputWithLabel">
								<input type="radio" id="textcenter" name="alignment" autocomplete="off" value="center" />
								<label for="textcenter">centered</label>
							</div>
							<div class="inputWithLabel">
								<input type="radio" id="textright" name="alignment" autocomplete="off" value="right" />
								<label for="textright">right-aligned</label>
							</div>
						</div>
						<input id="SpeedSlider" name="speedslider" hidden min="1" max="100" step="1" value={100} />
						<p class="card-title">What to Show</p>
						<div class="line">
							<div class="inputWithLabel">
								<input type="radio" id="modetext" name="devicemode" value="text" />
								<label for="modetext">Text</label>
							</div>
							<div class="inputWithLabel">
								<input type="radio" id="modedate" name="devicemode" value="date" />
								<label for="modedate">Date</label>
							</div>
							<div class="inputWithLabel">
								<input type="radio" id="modeclock" name="devicemode" value="clock" />
								<label for="modeclock">Clock</label>
							</div>
						</div>
						<input type="text" id="text" name="text" autocomplete="off" maxlength={16} />
						<input type="submit" value="Submit" />
					</div>
				</form>

				<div class="card">
					<p class="card-title">Offsets</p>
					<div class="line">
						{
							offsets.map((offset, index) => (
								<form action="/offset" method="post" id="offsetForm" onSubmit={handleFormSubmit}>
									<div class="offsetLine">
										<div class="inputWithLabel" key={index}>
											<label class="label" for="offset">Unit {index}</label>
											<input
												type="number"
												name="offset"
												value={offset}
												min={0}
												max={9999}
											/>
										</div>
										<input type="hidden" name="unit" value={index} />
										<input type="submit" value="Submit" id="offsetSubmitButton" />
									</div>
								</form>
							))
						}
					</div>
				</div>
			</div >
		</div>
	);
}

render(<App />, document.getElementById('app'));
