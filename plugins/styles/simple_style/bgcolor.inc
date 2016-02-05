<?php

$plugin = array(
  'title' => t('Border styles'),
  'description' => t('Style your border'),
  'render region' => 'border_style_render_region',
  'render pane' => 'border_style_render_pane',
  'pane settings form' => 'border_style_settings_form',//������ ���� ���������
  'settings form' => 'border_style_settings_form',// ������ ���� ���������
  'hook theme' => array(
    'border_theme' => array(
      'variables' => array('content' => '', 'classes' => '', 'style' => ''),
      'path' => drupal_get_path('module', 'simple_styles') . '/plugins/styles/simple_style',
      //'simple_styles' ��� ����� *.module
      'template' => 'border',
      //��� ����� *.tpl.php
    ),
  ),
);

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_border_style_render_region($variables) {
  $panes = $variables['panes'];
  $settings = $variables['settings'];
  $output = '';
  $border_style = $settings['bgcolor'];
  $qwert = $settings['b_width']; //������ border � px
  $bdr_width = "border-width:" . $qwert . "px;"; //��������� css �����. ���������� ������ ������� �� $form['b_width']
  foreach ($panes as $pane) {
    $output .= theme('border_theme', array(
      'content' => $pane,
      'border_styles' => "border-$border_style",
      'bdr_width' => $bdr_width
    )); //
  }
  return $output;
}

/**
 * Render callback for a single pane.
 */
function theme_border_style_render_pane($variables) {
  $content = $variables['content'];
  if (empty($content->content)) {
    return;
  }

  $pane = $variables['pane'];
  $display = $variables['display'];
  $settings = $variables['settings'];
  $qwert = $settings['b_width']; //�������� �������� �� $form['b_width']
  $border_style = $settings['bgcolor']; //pyfx
  $output_std = theme('panels_pane', array(
    'content' => $content,
    'pane' => $pane,
    'display' => $display
  )); //����������� �����������
  $bdr_width = "border-width:" . $qwert . "px;"; //��������� css �����. ���������� ������ ������� �� $form['b_width']
  $output = theme('border_theme', array(
    'content' => $output_std,
    'border_styles' => "border-$border_style",
    'bdr_width' => $bdr_width
  ));//"border-border_style" ��������� ������ - �������� css ������
  drupal_add_css(drupal_get_path('module', 'simple_styles') . '/plugins/styles/simple_style/simple.css');
  return $output;
}

/**
 * Settings form callback.
 */
function border_style_settings_form($style_settings) {

  $form['bgcolor'] = array( // ����� ������ �����
    '#type' => 'select',
    '#title' => t('Border style'),
    '#options' => array(
      'solid' => t('Solid'),
      'dotted' => t('Dotted'),
      'dashed' => t('Dashed'),
      'double' => t('Double'),
      'groove' => t('Groove'),
    ),
    '#default_value' => (isset($style_settings['bgcolor'])) ? $style_settings['bgcolor'] : 'solid',
    '#description' => t('Choose a border style.'),
  );

  $form['b_width'] = array( //����� ������ �������
    '#title' => t('Enter border width'),
    '#type' => 'textfield',
    '#default_value' => (isset($style_settings['b_width'])) ? $style_settings['b_width'] : 5,
  );
  return $form;
}
