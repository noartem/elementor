//
// Created by admin on 17.02.2024.
//

#ifndef EXAMPLES_CRUD_H
#define EXAMPLES_CRUD_H

#include "../elementor.h"

class Crud : public Component {
public:
	explicit Crud(const std::shared_ptr<ApplicationContext>& ctx)
		: Component(ctx) {
		element = Background::New(ctx, {
			.color = "#fff",
			.child = Padding::New(ctx, {
				.all = 32,
				.child = Flex::New(ctx, {
					.spacing = 8,
					.direction = FlexDirection::Column,
					.alignment = FlexAlignment::Center,
					.crossAlignment = FlexCrossAlignment::Center,
					.children = {
						Flex::New(ctx, {
							.spacing = 8,
							.children = {
								Flexible::New(ctx, {
									.child = Flex::New(ctx, {
										.spacing = 8,
										.direction = FlexDirection::Column,
										.children = {
											Flex::New(ctx, {
												.spacing = 8,
												.alignment = FlexAlignment::Center,
												.children = {
													Height::New(ctx, {
														.height = 10,
														.child =Text::New(ctx, {
															.text = "Filter prefix: ",
															.fontColor = "#000",
															.fontFamily = "Arial",
														})
													}),
													Flexible::New(ctx, {
														.child = TextInput::New(ctx),
													})
												}
											}),
											Flexible::New(ctx, {
												.child = Rounded::New(ctx, {
													.all = 8,
													.child = Background::New(ctx, {
														.color = "#ebf0f0",
														.child = Flex::New(ctx, {
															.direction = FlexDirection::Column,
															.alignment = FlexAlignment::Stretch,
															.children = {
																Padding::New(ctx, {
																	.all = 8,
																	.bottom = 10,
																	.child = Text::New(ctx, {
																		.text = "Emil, Hans",
																		.fontColor = "#000",
																		.fontSize = 12,
																		.fontFamily = "Arial",
																	})
																}),
																Padding::New(ctx, {
																	.all = 8,
																	.bottom = 10,
																	.child = Text::New(ctx, {
																		.text = "Mustermann, Max",
																		.fontColor = "#000",
																		.fontSize = 12,
																		.fontFamily = "Arial",
																	})
																}),
																Background::New(ctx, {
																	.color = "#ff5020",
																	.child = Padding::New(ctx, {
																		.all = 8,
																		.bottom = 10,
																		.child = Text::New(ctx, {
																			.text = "Tisch, Roman",
																			.fontColor = "#fff",
																			.fontSize = 12,
																			.fontFamily = "Arial",
																		})
																	})
																})
															}
														})
													})
												})
											})
										}
									})
								}),
								Flexible::New(ctx, {
									.child = Flex::New(ctx, {
										.spacing = 8,
										.direction = FlexDirection::Column,
										.children = {
											Flex::New(ctx, {
												.spacing = 8,
												.alignment = FlexAlignment::Center,
												.children = {
													Flexible::New(ctx, {
														.child = Align::New(ctx, {
															.width = { 1, 1 },
															.child = Text::New(ctx, {
																.text = "Name:",
															})
														})
													}),
													Flexible::New(ctx, {
														.child = TextInput::New(ctx),
													})
												}
											}),
											Flex::New(ctx, {
												.spacing = 8,
												.alignment = FlexAlignment::Center,
												.children = {
													Flexible::New(ctx, {
														.child = Align::New(ctx, {
															.width = { 1, 1 },
															.child = Text::New(ctx, {
																.text = "Surname:",
															})
														})
													}),
													Flexible::New(ctx, {
														.child = TextInput::New(ctx),
													})
												}
											})
										}
									})
								})
							}
						}),
						Flex::New(ctx, {
							.spacing = 8,
							.alignment = FlexAlignment::Center,
							.children = {
								Height::New(ctx, {
									.height = 28,
									.child = TextButton::New(ctx, {
										.text = "Create",
										.fontColor = "#fff",
										.backgroundColor = "#ff5020",
									}),
								}),
								Height::New(ctx, {
									.height = 28,
									.child = TextButton::New(ctx, {
										.text = "Update",
										.fontColor = "#fff",
										.backgroundColor = "#ff5020",
									}),
								}),
								Height::New(ctx, {
									.height = 28,
									.child = TextButton::New(ctx, {
										.text = "Delete",
										.fontColor = "#fff",
										.backgroundColor = "#ff5020",
									}),
								}),
							}
						})
					}
				})
			})
		});
	}

	static std::shared_ptr<Crud> New(const std::shared_ptr<ApplicationContext>& ctx) {
		return std::make_shared<Crud>(ctx);
	}

private:
	int count = 0;

	std::shared_ptr<Text> countText;

	void setCount(int newValue) {
		count = newValue;
		countText->setText(std::to_string(count));
	}

	void incCount() {
		setCount(count + 1);
	}
};

#endif //EXAMPLES_CRUD_H
