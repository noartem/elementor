//
// Created by admin on 17.02.2024.
//

#ifndef EXAMPLES_TODO_H
#define EXAMPLES_TODO_H

#include <fstream>

#include "../elementor.h"
#include "../assets/include.h"

class Todo : public Component {
public:
	struct Props {
		std::string filename;
	};

	Todo(const std::shared_ptr<ApplicationContext>& ctx, const Props& props)
		: Component(ctx) {
		filename = props.filename;
		readFromFile();

		element = Background::New(ctx, {
			.color = "#fff",
			.child = Flex::New(ctx, {
				.direction = FlexDirection::Column,
				.alignment = FlexAlignment::Stretch,
				.children = {
					Background::New(ctx, {
						.color = "#ff5020",
						.child = Padding::New(ctx, {
							.all = 10,
							.child = Text::New(ctx, {
								.text = "TODO v0.0.1",
								.fontColor = "#fff",
								.fontSize = 16,
								.fontWeight = 700,
								.fontFamily = "Fira Code",
							})
						})
					}),
					Padding::New(ctx, {
						.y = 8,
						.right = 16,
						.left = 12,
						.child = MakeTodoForm::New(ctx, {
							.onSubmit = [this](const std::string& text) {
								addItem(text);
								return true;
							}
						})
					}),
					Flexible::New(ctx, {
						.child = Scrollbar::New(ctx, {
							.thickness = 8,
							.spacing = 2,
							.thumb = Rounded::New(ctx, {
								.all = 8,
								.child = Background::New(ctx, {
									.color = "#ff5020",
								})
							}),
							.child = Scrollable::New(ctx, {
								.direction = ScrollDirection::Vertical,
								.child = Padding::New(ctx, {
									.y = 8,
									.right = 16,
									.left = 12,
									.child = TodoItems::New(ctx, itemsElement, {
										.items = items,
										.onToggle = [this](int i) {
											toggleItem(i);
										},
										.onRemove = [this](int i) {
											removeItem(i);
										},
										.onInput = [this](int i, const std::string& text) {
											changeItem(i, text);
										}
									})
								})
							})
						})
					})
				}
			})
		});
	}

	static std::shared_ptr<Todo> New(
		const std::shared_ptr<ApplicationContext>& ctx,
		const Props& props
	) {
		return std::make_shared<Todo>(ctx, props);
	}

private:
	struct TodoItemData {
		std::string text;
		bool done;
	};

	class MakeTodoForm : public Component {
	public:
		struct Props {
			std::function<bool(const std::string&)> onSubmit;
		};

		MakeTodoForm(const std::shared_ptr<ApplicationContext>& ctx, const Props& props)
			: Component(ctx) {
			submitCallback = props.onSubmit;

			element = Flex::New(ctx, {
				.spacing = 10,
				.alignment = FlexAlignment::Center,
				.children = {
					Flexible::New(ctx, {
						.child = TextInput::New(ctx, textInput, {
							.placeholder = U"Add item...",
							.onSubmit = [this](const std::u32string& newValue) {
								onSubmit();
							}
						}),
					}),
					IconButton::New(ctx, {
						.src = asset("add.svg"),
						.onClick = [this]() {
							onSubmit();
							return EventCallbackResponse::None;
						}
					})
				},
			});
		}

		static std::shared_ptr<MakeTodoForm> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const Props& props
		) {
			return std::make_shared<MakeTodoForm>(ctx, props);
		}
	private:
		std::shared_ptr<TextInput> textInput;

		std::function<bool(const std::string&)> submitCallback;

		void onSubmit() {
			auto value = textInput->getValue();
			if (value.empty()) {
				return;
			}

			auto processed = submitCallback(value);
			if (!processed) {
				return;
			}

			textInput->setValue("");
		}
	};

	class TodoItem : public Component {
	public:
		struct Props {
			std::string text;
			bool done;
			std::function<void()> onToggle;
			std::function<void()> onRemove;
			std::function<void(const std::string&)> onInput;
		};

		explicit TodoItem(const std::shared_ptr<ApplicationContext>& ctx, const Props& props)
			: Component(ctx) {
			element = Flex::New(ctx, {
				.spacing = 10,
				.alignment = FlexAlignment::Center,
				.children = {
					IconButton::New(ctx, {
						.src = props.done
							   ? asset("check_box.svg")
							   : asset("check_box_blank.svg"),
						.onClick = [props]() {
							props.onToggle();
							return EventCallbackResponse::None;
						}
					}),
					Flexible::New(ctx, {
						.child = makeContentElement(props),
					}),
					IconButton::New(ctx, {
						.src = asset("delete.svg"),
						.onClick = [props]() {
							props.onRemove();
							return EventCallbackResponse::None;
						}
					}),
				}
			});
		}

		static std::shared_ptr<TodoItem> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const Props& props
		) {
			return std::make_shared<TodoItem>(ctx, props);
		}
	private:
		std::shared_ptr<Element> makeContentTextElement(const Props& props) {
			return Padding::New(ctx, {
				.all = 6,
				.child = Paragraph::New(ctx, {
					.children = {
						Text::New(ctx, {
							.text = props.text,
							.fontColor = "#aaa",
							.fontSize = 14,
							.fontFamily = "Arial",
						}),
					}
				})
			});
		}

		std::shared_ptr<Element> makeContentInputElement(const Props& props) {
			return TextInput::New(ctx, {
				.value = fromUTF8(props.text),
				.onInput = [props](const std::u32string& newValue) {
					auto newValueU8 = toUTF8(newValue);
					if (newValueU8 == props.text) {
						return;
					}

					props.onInput(newValueU8);
				}
			});
		}

		std::shared_ptr<Element> makeContentElement(const Props& props) {
			if (props.done) {
				return makeContentTextElement(props);
			} else {
				return makeContentInputElement(props);
			}
		}
	};

	class TodoItems : public Component {
	public:
		struct Props {
			std::vector<TodoItemData> items;
			std::function<void(int i)> onToggle;
			std::function<void(int i)> onRemove;
			std::function<void(int i, const std::string& text)> onInput;
		};

		explicit TodoItems(const std::shared_ptr<ApplicationContext>& ctx, const Props& props)
			: Component(ctx) {
			items = props.items;
			toggleCallback = props.onToggle;
			removeCallback = props.onRemove;
			inputCallback = props.onInput;

			element = Column::New(ctx, itemsColumn, {
				.spacing = 8,
				.children = makeItemsElements(),
			});
		}

		static std::shared_ptr<TodoItems> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			const Props& props
		) {
			return std::make_shared<TodoItems>(ctx, props);
		}

		static std::shared_ptr<TodoItems> New(
			const std::shared_ptr<ApplicationContext>& ctx,
			std::shared_ptr<TodoItems>& elementRef,
			const Props& props
		) {
			auto element = New(ctx, props);
			elementRef = element;
			return element;
		}

		void setItems(const std::vector<TodoItemData>& newItems) {
			items = newItems;
			updateItemsElement();
		}

	private:
		std::vector<TodoItemData> items;

		std::function<void(int i)> toggleCallback;
		std::function<void(int i)> removeCallback;
		std::function<void(int i, const std::string& text)> inputCallback;

		std::shared_ptr<Column> itemsColumn;

		std::vector<std::shared_ptr<Element>> makeItemsElements() {
			std::vector<std::shared_ptr<Element>> itemsElements;

			for (int i = 0; i < items.size(); ++i) {
				itemsElements.push_back(
					TodoItem::New(ctx, {
						.text = items[i].text,
						.done = items[i].done,
						.onToggle = [this, i]() {
							toggleCallback(i);
							return EventCallbackResponse::None;
						},
						.onRemove = [this, i]() {
							removeCallback(i);
							return EventCallbackResponse::None;
						},
						.onInput = [this, i](const std::string& text) {
							inputCallback(i, text);
							return EventCallbackResponse::None;
						}
					})
				);
			}

			return itemsElements;
		}

		void updateItemsElement() {
			itemsColumn->setChildren(makeItemsElements());
		}
	};

	std::string filename;
	std::vector<TodoItemData> items;

	std::shared_ptr<TodoItems> itemsElement;

	void readFromFile() {
		std::ifstream file(filename);

		std::string line;
		while (std::getline(file, line)) {
			if (line.substr(0, 6) == "- [x] ") {
				items.push_back({
					.text = line.substr(6),
					.done = true,
				});
			} else if (line.substr(0, 6) == "- [ ] ") {
				items.push_back({
					.text = line.substr(6),
					.done = false,
				});
			}
		}
	}

	void writeToFile() {
		std::ofstream file(filename);

		for (const auto& item: items) {
			file << "- [" << (item.done ? "x" : " ") << "] " << item.text << "\n";
		}
	}

	bool pendingUpdateItems = false;

	void updateItems() {
		itemsElement->setItems(items);
		writeToFile();
	}

	void pendUpdateItems() {
		pendingUpdateItems = true;
		ctx->requestNextFrame([this]() {
			if (pendingUpdateItems) {
				updateItems();
				pendingUpdateItems = false;
			}
		});
	}

	void addItem(const std::string& text) {
		D_LOG("Adding item \"" << text << "\"");
		items.push_back({
			.text = text,
			.done = false,
		});
		pendUpdateItems();
	}

	void toggleItem(unsigned i) {
		D_LOG("Toggling " << i << "th item");
		items[i].done = !items[i].done;
		pendUpdateItems();
	}

	void removeItem(unsigned i) {
		D_LOG("Removing " << i << "th item");
		items.erase(items.begin() + i);
		pendUpdateItems();
	}

	void changeItem(unsigned i, const std::string& text) {
		D_LOG("Changing " << i << "th item to \"" << text << "\"");
		if (items[i].done) {
			return;
		}
		items[i].text = text;
		pendUpdateItems();
	}
};


#endif //EXAMPLES_TODO_H
